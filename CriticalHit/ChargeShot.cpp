#include "pch.h"
#include "ChargeShot.h"
#include "DeviceResources.h"
#include "View.h"
#include "CollisionManager.h"
#include "GameContext.h"
#include "Adx2Le.h"
#include "Resources\Sound\Soundcue.h"

ChargeShot::ChargeShot(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth, float power)
	: GameObject("Bullet")
	, m_velocity(azimuth * MOVE_BASESPEED)
	, m_radius(0.5f)
	, m_power(power)
	, m_isShot(true)
	, m_length(0.0f)
	, m_colFlag(false)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, m_radius);

	m_position = position;
	m_position.z = position.z - 0.5f;

	m_radius *= m_power;

	m_scale = DirectX::SimpleMath::Vector3(m_radius, m_radius, m_radius);
	m_collider = std::make_unique<SphereCollider>(this, m_scale.x / 2);

	GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_CHARGESHOT);
}


ChargeShot::~ChargeShot()
{
}

void ChargeShot::Update(float elapsedTime)
{

		m_position += m_velocity;
		m_length += m_velocity.Length();
	if (m_length > MAXMUM_RANGE || m_colFlag)
	{
		Destroy(this);
	}

	GameContext<CollisionManager>::Get()->add(m_collider.get());
}

void ChargeShot::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(m_radius);
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	Projection* proj = GameContext<Projection>::Get();
	View* view = GameContext<View>().Get();

	m_geometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::OrangeRed);
}

void ChargeShot::OnCollision(GameObject * object)
{
	if (object->GetTag() != "Player" && object->GetTag() != "Bullet" && object->GetTag() != "EnemyBullet")
	{
		m_colFlag = true;
	}
}
