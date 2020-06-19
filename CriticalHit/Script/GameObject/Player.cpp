#include "pch.h"
#pragma warning(disable: 4100)
#include "Player.h"
#include "Bullet.h"
#include "ChargeShot.h"

#include <memory>
#include <math.h>
#include <vector>
#include <Keyboard.h>
#include <Mouse.h>
#include <Effects.h>
#include <VertexTypes.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "GameSceneManager.h"
#include "ScoreManager.h"
#include "View.h"
#include "Font.h"
#include "Reticule.h"

#include "Adx2Le.h"
#include "Resources\Sound\Soundcue.h"

Player::Player(const DirectX::SimpleMath::Vector3& position, float fireInterval)
	: GameObject("Player")
	, m_fireInterval(fireInterval)
	, m_elapsedTime(0.0f)
	, m_isLoading(false)
	, m_horizontalAngle(-180.0f)
	, m_pGeometricPrimitive()
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_shotPower(0.0f)
	, m_chargeInterval(0)
	, m_laserPoint(0)
	, m_laserCount(0)
	, m_lastScore(0)
	, m_hp(MAX_HP)
	, m_state(STATE::NORMAL_STATE)

{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	
	m_scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 1.0f);
	m_position = position;
	m_collider = std::make_unique<BoxCollider>(this, m_scale);
	m_rotation = DirectX::SimpleMath::Vector3(0.0f, 180.0f, 0.0f);

	m_pMouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	m_colFlag = false;
	m_pGeometricPrimitive = DirectX::GeometricPrimitive::CreateBox(deviceContext, m_scale);
	// モデル描画準備
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(deviceResources->GetD3DDevice());

	factory->SetDirectory(L"Resources/Models");

	m_pModel = DirectX::Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/aircraft.cmo",
		*factory);

	delete factory;
	// スコアマネージャーに初期HPを登録
	// スコアマネージャーシングルトンはなんか無駄なので改良はコンテキスト追加でお願いします
	ScoreManager::GetInstance()->SetPlayerHP(m_hp);
	ScoreManager::GetInstance()->SetPlayerSP(m_laserPoint);
	ScoreManager::GetInstance()->SetPlayerCP(m_shotPower);
}

Player::~Player()
{

}

void Player::Update(float elapsedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* key = GameContext<DirectX::Keyboard::KeyboardStateTracker>::Get();
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	m_pMouseTracker->Update(mouseState);

	// 速度は毎回初期化
	m_velocity = DirectX::SimpleMath::Vector3::Zero;
	
	if (m_state != STATE::SPECIAL_STATE)
	{
		int score = ScoreManager::GetInstance()->GetScore();
		m_laserPoint = (score - m_lastScore);

		// 上限
		if (m_laserPoint > 5)
		{
			m_laserPoint = 5;
		}
	}
	switch (m_state)
	{
	case Player::DEMO_STATE:
		DemoState(elapsedTime);
		break;
	case Player::NORMAL_STATE:
		NormalState(elapsedTime);
		break;
	case Player::CHARGE_STATE:
		ChargeState(elapsedTime);
		break;
	case Player::SPECIAL_STATE:
		SpecioalState(elapsedTime);
		break;
	case Player::DESTROY_STATE:
		DestroyState(elapsedTime);
		break;
	case Player::CLEAR_STATE:
		ClearState(elapsedTime);
		break;
	default:
		break;
	}
	// デバッグモード時
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		if (key->IsKeyPressed(DirectX::Keyboard::C))
		{
			ScoreManager::GetInstance()->AddScore(5);
		}
		// 当たり判定更新
		DirectX::SimpleMath::Vector3 ColPos = m_collider->GetPosition();
		DirectX::SimpleMath::Vector3 ColOffSet = m_collider->GetOffset();
		// 弾丸情報
		/*Font::GetInstance()->Print(L"PlayerColPos", 0, 120, L"プレイヤー座標：%f,%f,%f", ColPos.x, ColPos.y, ColPos.z);
		Font::GetInstance()->Print(L"PlayerColOff", 0, 150, L"プレイヤーサイズ：%f,%f,%f", ColOffSet.x, ColOffSet.y, ColOffSet.z); */
	}
	else
	{
		//// 必要情報文字出力
		//Font::GetInstance()->Print(L"HP", 0, 0, L"プレイヤーHP：%d", m_hp);
		//Font::GetInstance()->Print(L"Charge", 0, 150, L"チャージ：%f", m_shotPower);
		//Font::GetInstance()->Print(L"Laser", 0, 180, L"乱射ゲージ：%d", m_laserPoint);
	}
	m_position += m_velocity;

	GameContext<CollisionManager>::Get()->add(m_collider.get());
	ScoreManager::GetInstance()->SetPlayerSP(m_laserPoint);
	ScoreManager::GetInstance()->SetPlayerCP(m_shotPower);
}



void Player::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotation.x));
	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians( m_rotation.y));
	world *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation.z));
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// モデル描画
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	Projection* proj = GameContext<Projection>().Get();
	View* view = GameContext<View>().Get();
	DirectX::CommonStates* states = GameContext<DirectX::CommonStates>().Get();
	/*DirectX::BasicEffect* effects = GameContext<DirectX::BasicEffect>().Get();*/

	// モデル描画にはコモンステートいるよ！
	m_pModel->Draw(deviceContext, *states, world, view->GetMatrix(), proj->GetMatrix());
	if (m_debugMode)
	{
		// 当たり判定の可視化
		world = DirectX::SimpleMath::Matrix::Identity;
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_collider->GetPosition());

		m_pGeometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Red, nullptr, true);
	}
}

void Player::OnCollision(GameObject * object)
{
	if (m_state != STATE::DESTROY_STATE)
	{
		if (object->GetTag() == "EnemyBullet")
		{
			// ダメージサウンド
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_HIT);
			// HPを減算
			m_hp--;
			// スコアマネージャーを更新
			ScoreManager::GetInstance()->SetPlayerHP(m_hp);
			Destroy(object);
		}
	}
}
// 更新処理(デモの時
void Player::DemoState(float elapsedTime)
{
}
// 更新処理(基本の時
void Player::NormalState(float elapsedTime)
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	Move(elapsedTime);

	if (m_isLoading)
	{
		m_elapsedTime += elapsedTime;

		if (m_elapsedTime > m_fireInterval)
		{
			m_isLoading = false;
		}
	}
	// 弾を撃つ
	if (!m_isLoading)
	{
		// 通常弾
		if (m_pMouseTracker->leftButton == m_pMouseTracker->HELD)
		{
			Shot(0);
		}
		// チャージ弾(通常弾と同時に発射できないように
		else if(m_pMouseTracker->rightButton == m_pMouseTracker->HELD)
		{	
			m_state = STATE::CHARGE_STATE;
		}
		// レーザー
		if (m_pMouseTracker->middleButton == m_pMouseTracker->PRESSED && m_laserPoint >= 5)
		{
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_SPECIAL);
			m_state = STATE::SPECIAL_STATE;
		}
	}
	
	if (m_hp <= 0)
	{
		GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_EXPLOSION);
		m_hp = 0;
		m_state = STATE::DESTROY_STATE;
	}
}
// 更新処理(チャージ中の時
void Player::ChargeState(float elapsedtime)
{
	Move(elapsedtime);
	if (m_pMouseTracker->rightButton == m_pMouseTracker->HELD)
	{
		if (m_chargeInterval >= 8)
		{
			m_shotPower += 1.0f;
			if (m_shotPower > 5.0f)
				m_shotPower = 5.0f;
			m_chargeInterval = 0;
		}
		else
		{
			m_chargeInterval++;
		}
		
	}
	if (m_pMouseTracker->rightButton == m_pMouseTracker->RELEASED)
	{
		// ボタンから離されたらチャージした弾を発射
		Shot(1);
		m_shotPower = 0.0f;
		m_chargeInterval = 0;
		m_state = STATE::NORMAL_STATE;
	}
}
// 更新処理(スペシャル発動中の時
void Player::SpecioalState(float elapsedTime)
{
	Move(elapsedTime);
	m_elapsedTime += elapsedTime;
	if (m_elapsedTime > m_fireInterval - 0.1f)
	{
		Shot();
	}
	m_laserCount++;
	if (m_laserCount > 120)
	{
		m_laserPoint--;
		m_laserCount = 0;
		if (m_laserPoint == 0)
		{
			m_lastScore = ScoreManager::GetInstance()->GetScore();
			m_state = STATE::NORMAL_STATE;
		}
	}
}
// 更新処理(破壊された時
void Player::DestroyState(float elapsedTime)
{
	// 撃墜姿勢
	m_velocity.y = -0.05f;
	m_rotation.x = 20.0f;
	m_rotation.z += 2.0f;

}
// 更新処理(クリアした時
void Player::ClearState(float elapsedTime)
{
}
// 移動処理
void Player::Move(float elapsedtime)
{
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	// 基準点からのx,y各々の距離を求める
	DirectX::SimpleMath::Vector2 base_length;
	base_length.x = std::abs(m_position.x - BASE_VEC.x);
	base_length.y = std::abs(m_position.y - BASE_VEC.y);
	// WASD移動
	// 上下移動
	if (key.IsKeyDown(DirectX::Keyboard::W))
	{
		m_velocity.y = MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE)
			m_velocity.y /= 2;
		m_rotation.x -= 2.0f;
		// 移動量制限処理
		if (base_length.y > 4.0f && BASE_VEC.y <= m_position.y)
			m_velocity.y = 0.0f;
	}
	else if (key.IsKeyDown(DirectX::Keyboard::S))
	{
		m_velocity.y = -MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE) m_velocity.y /= 2;
		m_rotation.x += 2.0f;
		// 移動量制限処理
		if (base_length.y > 4.0f && BASE_VEC.y > m_position.y)
			m_velocity.y = 0.0f;
	}
	else
	{
		// 少しずつ角度をもとに戻す
		if (m_rotation.x > 0)
		{
			m_rotation.x -= 2.0f;

		}
		else if (m_rotation.x < 0)
		{
			m_rotation.x += 2.0f;
		}
		else
		{
			m_rotation.x = 0.0f;

		}

	}
	// 左右移動
	if (key.IsKeyDown(DirectX::Keyboard::A))
	{
		m_velocity.x = -MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE) m_velocity.x /= 2;
		m_rotation.z += 3.0f;
		m_rotation.y += 2.0f;
		// 移動量制限処理
		if (base_length.x > 5.0f && BASE_VEC.x >= m_position.x)
			m_velocity.x = 0.0f;

	}
	else if (key.IsKeyDown(DirectX::Keyboard::D))
	{
		m_velocity.x = MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE) m_velocity.x /= 2;
		m_rotation.z -= 3.0f;
		m_rotation.y -= 2.0f;
		// 移動量制限処理
		if (base_length.x > 5.0f && BASE_VEC.x <= m_position.x)
			m_velocity.x = 0.0f;
	}
	else
	{
		// 少しずつ角度をもとに戻す
		if (m_rotation.z > 0)
		{
			m_rotation.z -= 1.0f;
		}
		else if (m_rotation.z < 0)
		{
			m_rotation.z += 1.0f;
		}
		else
		{
			m_rotation.z = 0.0f;
		}
		// 少しずつ角度をもとに戻す
		if (m_rotation.y > 180)
		{
			m_rotation.y -= 1.0f;
		}
		else if (m_rotation.y < 180)
		{
			m_rotation.y += 1.0f;
		}
		else
		{
			m_rotation.y = 180.0f;
		}
	}

	// 回転の調整
	// X軸
	if (m_rotation.x > 30.0f)
	{
		m_rotation.x = 30.0f;
	}
	else if (m_rotation.x < -30.0f)
	{
		m_rotation.x = -30.0f;
	}
	// Y軸
	if (m_rotation.y > 200.0f)
	{
		m_rotation.y = 200.0f;
	}
	else if (m_rotation.y < 160.0f)
	{
		m_rotation.y = 160.0f;
	}

	// Z軸
	if (m_rotation.z > 20.0f)
	{
		m_rotation.z = 20.0f;
	}
	else if (m_rotation.z < -20.0f)
	{
		m_rotation.z = -20.0f;
	}
}
// 弾丸発射処理
void Player::Shot(const int& shottype)
{

	/*float rad = DirectX::XMConvertToRadians(m_horizontalAngle + 90.0f);
	DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));*/
	
	// マウスの座標から方向を算出
	std::vector<GameObject*> reticule = GameContext<GameObjectManager>::Get()->Find("Pointer");
	DirectX::SimpleMath::Vector3 pointerPos = reticule.front()->GetPosition();
	DirectX::SimpleMath::Vector3 vec = pointerPos - m_position;
	vec.Normalize(); 

	switch (shottype)
	{
	case 0:
	{
		// 通常弾丸を生成
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(m_position, vec);
		GameContext<GameObjectManager>::Get()->Add(std::move(bullet));

		break;
	}
	case 1:
	{
		// チャージ弾丸を生成
		std::unique_ptr<ChargeShot> bullet = std::make_unique<ChargeShot>(m_position, vec,m_shotPower);
		GameContext<GameObjectManager>::Get()->Add(std::move(bullet));
		break;
	}
	default:
	{
		assert("選択された弾丸が存在しません。");
		break;
	}
	}
	m_elapsedTime = 0.0f;
	m_isLoading = true;
}


