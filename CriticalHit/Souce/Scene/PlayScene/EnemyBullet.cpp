#include "..\..\pch.h"
#include "EnemyBullet.h"

#include "..\..\DeviceResources.h"
#include "..\..\Manager\CollisionManager.h"
#include "..\..\View.h"

EnemyBullet::EnemyBullet(const DirectX::SimpleMath::Vector3 & position, const DirectX::SimpleMath::Vector3 & azimuth)
	: GameObject("EnemyBullet")
	, m_velocity(azimuth * MOVE_SPEED)
	, m_length(0.0f)
{
	m_position = position;

	m_scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

	// ジオメトリ作成
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, m_scale.x);

	m_collider = std::make_unique<SphereCollider>(this, m_scale.x);
	m_colflg = false;
}

void EnemyBullet::Update(float elapsedTime)
{
	// 不使用
	(void)elapsedTime;
	// 移動処理
	m_position += m_velocity;
	m_length += m_velocity.Length();

	GameContext<CollisionManager>::Get()->add(m_collider.get());
	if (m_length > MAXMUM_RANGE || m_colflg)
	{
		Destroy(this);
	}
}

void EnemyBullet::Render()
{
	// ジオメトリ描画処理
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	Projection* proj = GameContext<Projection>::Get();
	View* view = GameContext<View>().Get();

	m_geometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Blue);
}

void EnemyBullet::OnCollision(GameObject * object)
{
	if (object->GetTag() != "Enemy" && object->GetTag() != "EnemyBullet" && object->GetTag() != "Bullet")
	{
		m_colflg = true;
	}
}
