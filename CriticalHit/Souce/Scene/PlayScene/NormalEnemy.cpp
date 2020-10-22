#include "..\..\pch.h"

#include <Effects.h>

#include "NormalEnemy.h"
#include "EnemyBullet.h"
#include "..\..\DeviceResources.h"
#include "..\..\Manager\GameObjectManager.h"
#include "..\..\Manager\CollisionManager.h"
#include "..\..\Manager\ScoreManager.h"
#include "..\..\View.h"
#include "..\..\UI\Font.h"

#include "..\..\Adx2Le.h"
#include "..\..\Resources\Sound\Soundcue.h"

NormalEnemy::NormalEnemy(const DirectX::SimpleMath::Vector3& position)
	: GameObject("Enemy")
	, m_velocity(0.0f,0.0f,0.05f)
	, m_model(nullptr)
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
	m_count = 0.0f;
}

NormalEnemy::~NormalEnemy()
{
}

void NormalEnemy::Update(float elapsedTime)
{
	//m_count += 0.01f;

	/*m_velocity.x = 0.05 *  std::cosf(m_count);*/
	if (!m_isDown)
	{
		if (m_hitPoint <= 0.0f)
		{
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_EXPLOSION);
			ScoreManager::GetInstance()->AddScore(1);
			m_isDown = true;
		}
		if (DebugMode::GetInstance()->GetDebugMode())
		{
			Font::GetInstance()->Print(L"EnemyHP", 0.0f, 180.0f, L"敵HP：%f", m_hitPoint);
		}
		

		// プレイヤーの座標取得
		std::vector<GameObject*> player = GameContext<GameObjectManager>::Get()->Find("Player");
		DirectX::SimpleMath::Vector3 p_pos = player.back()->GetPosition();
		// 弾を撃つ処理　プレイヤーを通りすぎた後は処理しない
		if (m_count >= BULLET_INTERVAL && p_pos.z > m_position.z)
		{
			// プレイヤーの座標を取得
			DirectX::SimpleMath::Vector3 b_pos = m_position;
			b_pos.z += 3.0f;
			DirectX::SimpleMath::Vector3 vec = p_pos - b_pos;
			vec.Normalize();
			std::unique_ptr<EnemyBullet> bullet = std::make_unique<EnemyBullet>(b_pos, vec);
			GameContext<GameObjectManager>::Get()->Add(std::move(bullet));

			m_count = 0.0f;
		}
		if (p_pos.z + 3.0f < m_position.z)
		{
			m_velocity.y += 0.01;
			if (m_velocity.y >= 0.1f)
				m_velocity.y = 0.1f;
		}
		m_count += elapsedTime;
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
	m_position += m_velocity;

	GameContext<CollisionManager>::Get()->add(m_collider.get());
}

void NormalEnemy::Render()
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
	/*m_geometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Red);*/
	
	// デバッグ処理
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		world = DirectX::SimpleMath::Matrix::Identity;
		world = DirectX::SimpleMath::Matrix::CreateTranslation(m_collider->GetPosition());
		m_colliderGeometric->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Yellow, nullptr, true);
	}
}

void NormalEnemy::OnCollision(GameObject * object)
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
