#include "..\..\pch.h"
#pragma warning(disable: 4100)
#include "Bullet.h"


#include "..\..\DeviceResources.h"
#include "..\..\GameContext.h"
#include "..\..\Manager\CollisionManager.h"
#include "..\..\Manager\GameObjectManager.h"
#include "..\..\DebugMode.h"

#include "..\..\Projection.h"
#include "..\..\View.h"

#include "..\..\Adx2Le.h"
#include "..\..\Resources\Sound\Soundcue.h"

Bullet::Bullet(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth)
	: GameObject("Bullet")
	, m_velocity(azimuth * MOVE_SPEED)
	, m_origin(position)
	, m_length(0.0f)
	, m_isTargeting(false)
	, m_target(nullptr)
{
	m_position = position;
	m_position.z = position.z - 0.5f;

	m_scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
	
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, m_scale.x);

	m_colFlag = false;
	
	m_collider = std::make_unique<SphereCollider>(this, m_scale.x);
	/*float size = m_collider->GetRadius() / 2;*/
	m_colliderGeometric = DirectX::GeometricPrimitive::CreateSphere(deviceContext, Bullet::SERACH_RANGE);

	GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_SHOT);
}



Bullet::~Bullet()
{
}



void Bullet::Update(float elapsedTime)
{
	// 索敵処理

	// 索敵範囲距離にいる敵を見つける
	if (!m_isTargeting)
	{
		std::vector<GameObject*> enemy = GameContext<GameObjectManager>::Get()->Find("Enemy");
		// enemyのコンテナが空ではなかったとき
		if (!enemy.empty())
		{
			for (GameObject* i : enemy)
			{
				// 索敵範囲内にだったら
				if (DirectX::SimpleMath::Vector3::Distance(m_position, i->GetPosition()) <= Bullet::SERACH_RANGE)
				{
					m_target = i;
					m_isTargeting = true;
				}
			}
		}
	}
	else if(m_isTargeting)
	{
		m_velocity = m_target->GetPosition() - m_position;
		m_velocity.Normalize();
	}
	else
	{
		assert("このメッセージが見えるのはおかしいよ！");
	}
	

	
	// 移動処理
	m_position += m_velocity;
	m_length += m_velocity.Length();

	GameContext<CollisionManager>::Get()->add(m_collider.get());
	if (m_length > MAXMUM_RANGE || m_colFlag)
	{
		Destroy(this);
	}
	
}



void Bullet::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	Projection* proj = GameContext<Projection>::Get();
	View* view = GameContext<View>().Get();

	m_geometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::DarkGreen);
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		world = DirectX::SimpleMath::Matrix::Identity;
		DirectX::SimpleMath::Vector3 colPos = m_collider->GetPosition();
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(colPos);

		m_colliderGeometric->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Yellow, nullptr, true);
	}
}


void Bullet::OnCollision(GameObject * object)
{
	if (object->GetTag() != "Enemy" && object->GetTag() != "Bullet" && object->GetTag() != "EnemyBullet" && object->GetTag() != "Player")
	{
		m_colFlag = true;
	}
	
}
