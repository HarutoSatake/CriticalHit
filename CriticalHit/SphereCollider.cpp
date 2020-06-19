#include "pch.h"
#include "SphereCollider.h"


SphereCollider::SphereCollider(GameObject * object, float radius)
	: Collider(object)
	, m_radius(radius)
{
}

float SphereCollider::GetRadius() const
{
	return m_radius;
}

void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}
