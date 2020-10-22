#include "..\pch.h"
#include "BoxCollider.h"


BoxCollider::BoxCollider(GameObject * object, const DirectX::SimpleMath::Vector3 & size)
	: Collider(object)
{
	m_size.x = size.x / 2;
	m_size.y = size.y / 2;
	m_size.z = size.z / 2;
}

void BoxCollider::SetSize(const DirectX::SimpleMath::Vector3& size)
{
	m_size.x = size.x / 2;
	m_size.y = size.y / 2;
	m_size.z = size.z / 2;
}

const DirectX::SimpleMath::Vector3& BoxCollider::GetSize() const
{
	return m_size;
}
