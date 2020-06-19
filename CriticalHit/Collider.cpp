#include "pch.h"
#include "Collider.h"

#include "GameObject.h"

Collider::Collider(GameObject* object)
	: m_object(object),
	m_offset(DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f))
{
}

// Unity“I‚È
void Collider::OnCollision(const Collider* object)
{
	m_object->OnCollision(object->m_object);
}

const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
{
	return m_object->GetPosition()/* + m_offset*/;
}

const DirectX::SimpleMath::Vector3 Collider::GetOffset() const
{
	return m_offset;
}

void Collider::SetOffset(const DirectX::SimpleMath::Vector3 &offset)
{
	m_offset = offset;
}