#include "pch.h"
#include <Effects.h>
#include "WaveMoveEnemy.h"
#include "DeviceResources.h"
#include "GameObjectManager.h"
#include "EnemyBullet.h"
#include "CollisionManager.h"
#include "ScoreManager.h"
#include "View.h"
#include "Font.h"

#include "Adx2Le.h"
#include "..\..\Resources\Sound\Soundcue.h"

WaveMoveEnemy::WaveMoveEnemy(const DirectX::SimpleMath::Vector3& position)
	: GameObject("Enemy")
	, m_velocity(0.0f,0.0f,0.05f)
	, m_count(0.0f)
	, m_isDown(false)
{

	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateCone(deviceContext);
	m_scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	m_position = position;
	
	// モデル描画準備
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(deviceResources->GetD3DDevice());

	factory->SetDirectory(L"Resources/Models");

	m_model = DirectX::Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/Enemy.cmo",
		*factory);

	delete factory;
	// 当たり判定
	m_collider = std::make_unique<BoxCollider>(this, m_scale);
	DirectX::SimpleMath::Vector3 size = m_collider->GetSize();
	m_colliderGeometric = DirectX::GeometricPrimitive::CreateBox(deviceContext, m_scale);
	
	m_hitPoint = 5.0f;
	m_time = 0.0f;
}

WaveMoveEnemy::~WaveMoveEnemy()
{
}

void WaveMoveEnemy::Update(float elapsedTime)
{
	if (!m_isDown)
	{
		m_time += elapsedTime;

		// 波のように動いてほしい
		m_velocity.x = 0.05f * std::sinf(m_time);
		m_velocity.y = 0.05f * std::sinf(m_time * 5);

		if (m_hitPoint <= 0.0f)
		{
			// 爆発サウンド
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_EXPLOSION);
			ScoreManager::GetInstance()->AddScore(1);
			m_isDown = true;
			/*m_isDown = true;*/
		}
		// プレイヤーの座標取得
		std::vector<GameObject*> player = GameContext<GameObjectManager>::Get()->Find("Player");
		DirectX::SimpleMath::Vector3 p_pos = player.back()->GetPosition();
		// 弾を撃つ処理　プレイヤーを通りすぎた後は処理しない
		if (m_count >= BULLET_INTERVAL && p_pos.z > m_position.z)
		{
			// プレイヤーの座標を取得

			DirectX::SimpleMath::Vector3 vec = p_pos - m_position;
			vec.Normalize();

			std::unique_ptr<EnemyBullet> bullet = std::make_unique<EnemyBullet>(m_position, vec);
			GameContext<GameObjectManager>::Get()->Add(std::move(bullet));

			m_count = 0.0f;
		}
		m_count += elapsedTime;
		// プレイヤー通り過ぎたら上に上がる
		if (p_pos.z + 3.0f < m_position.z)
		{
			m_velocity.y += 0.01;
			if (m_velocity.y >= 0.1f)
				m_velocity.y = 0.1f;
		}
	}
	else
	{
		// 撃墜姿勢
		m_velocity.y = -0.05f;
		m_rotation.x = 20.0f;
		m_rotation.z += 2.0f;

		// 画面外までオブジェクト破棄
		if (m_position.y <= -4.0f)
		{
			Destroy(this);
		}
	}
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		Font::GetInstance()->Print(L"EnemyHP", 0.0f, 180.0f, L"敵HP：%f", m_hitPoint);
	}

	GameContext<CollisionManager>::Get()->add(m_collider.get());

	m_position += m_velocity;
}

void WaveMoveEnemy::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotation.x));
	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y));
	world *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation.z));
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	View* view = GameContext<View>().Get();
	Projection* proj = GameContext<Projection>().Get();
	DirectX::CommonStates* states = GameContext<DirectX::CommonStates>().Get();

	m_model->Draw(deviceContext, *states, world, view->GetMatrix(), proj->GetMatrix());
	// デバッグ処理
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		world = DirectX::SimpleMath::Matrix::Identity;
		world = DirectX::SimpleMath::Matrix::CreateTranslation(m_collider->GetPosition());
		m_colliderGeometric->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Yellow, nullptr, true);
	}
}

void WaveMoveEnemy::OnCollision(GameObject * object)
{
	if (object->GetTag() == "Bullet")
	{
		if (m_hitPoint > 0)
		{
			// ダメージサウンド
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_HIT);
			m_hitPoint -= object->GetScale().x / 0.5f;
		}
		Destroy(object);
	}
}
