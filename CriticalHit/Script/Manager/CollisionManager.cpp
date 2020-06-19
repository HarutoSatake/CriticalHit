#include "pch.h"
#include "CollisionManager.h"

#include <typeinfo>

#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Utilities.h"
#include "Font.h"
CollisionManager::CollisionManager()
	:m_colliders()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::add(Collider * collider)
{
	m_colliders.push_back(collider);
}

void CollisionManager::DetectCollision()
{
	int numObjects = static_cast<int>(m_colliders.size());

	// ìÒÇ¬Ç∏Ç¬êiÇÒÇ≈Ç¢Ç≠
	for (int i = 0; i < numObjects - 1; i++)
	{
		for (int j = i + 1; j < numObjects; j++)
		{
			if (IsCollided(m_colliders[i], m_colliders[j]))
			{
				m_colliders[i]->OnCollision(m_colliders[j]);
				m_colliders[j]->OnCollision(m_colliders[i]);
			}
		}
	}

	m_colliders.clear();
}

bool CollisionManager::IsCollided(const Collider * collider1, const Collider * collider2) const
{
	static const size_t TYPE_SPHERE = typeid(SphereCollider).hash_code();
	static const size_t TYPE_BOX = typeid(BoxCollider).hash_code();

	size_t collider1Type = typeid(*collider1).hash_code();
	size_t collider2Type = typeid(*collider2).hash_code();


	if ((collider1Type == TYPE_SPHERE) && (collider2Type == TYPE_SPHERE))
	{
		return IsCollided(dynamic_cast<const SphereCollider*>(collider1), dynamic_cast<const SphereCollider*>(collider2));
	}

	if ((collider1Type == TYPE_BOX) && (collider2Type == TYPE_BOX))
	{
		return IsCollided(dynamic_cast<const BoxCollider*>(collider1), dynamic_cast<const BoxCollider*>(collider2));
	}

	if ((collider1Type == TYPE_SPHERE) && (collider2Type == TYPE_BOX))
	{
		return IsCollided(dynamic_cast<const SphereCollider*>(collider1), dynamic_cast<const BoxCollider*>(collider2));
	}

	if ((collider1Type == TYPE_BOX) && (collider2Type == TYPE_SPHERE))
	{
		return IsCollided(dynamic_cast<const BoxCollider*>(collider1), dynamic_cast<const SphereCollider*>(collider2));
	}

	return false;
}

bool CollisionManager::IsCollided(const SphereCollider * collider1, const SphereCollider * collider2) const
{
	// íÜêSä‘ÇÃãóó£ÇÃïΩï˚ÇåvéZ
	
	DirectX::SimpleMath::Vector3 d = collider1->GetPosition() - collider2->GetPosition();
	float dist2 = d.Dot(d);
	// ïΩï˚ÇµÇΩãóó£Ç™ïΩï˚ÇµÇΩîºåaÇÃçáåvÇÊÇËÇ‡è¨Ç≥Ç¢èÍçáÇ…ãÖÇÕåç∑ÇµÇƒÇ¢ÇÈ
	float radiusSum = collider1->GetRadius() + collider2->GetRadius();
	return dist2 <= radiusSum * radiusSum;
}

bool CollisionManager::IsCollided(const BoxCollider * collider1, const BoxCollider * collider2) const
{
	DirectX::SimpleMath::Vector3 col1Pos = collider1->GetPosition();
	DirectX::SimpleMath::Vector3 col2Pos = collider2->GetPosition();
	DirectX::SimpleMath::Vector3 col1Size = collider1->GetSize();
	DirectX::SimpleMath::Vector3 col2Size = collider2->GetSize();
	if (fabsf(col1Pos.x - col2Pos.x) > (col1Size.x + col2Size.x)) return false;
	if (fabsf(col1Pos.y - col2Pos.y) > (col1Size.y + col2Size.y)) return false;
	if (fabsf(col1Pos.z - col2Pos.z) > (col1Size.z + col2Size.z)) return false;
	return true;
}

bool CollisionManager::IsCollided(const SphereCollider * collider1, const BoxCollider * collider2) const
{
	float sqDist = SqDistPointBox(collider1->GetPosition(), collider2);
	return sqDist <= collider1->GetRadius() * collider1->GetRadius();
}

bool CollisionManager::IsCollided(const BoxCollider * collider1, const SphereCollider * collider2) const
{
	float sqDist = SqDistPointBox(collider2->GetPosition(), collider1);
	return sqDist <= collider2->GetRadius() * collider2->GetRadius();
}

float CollisionManager::SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const BoxCollider* b)
{
	DirectX::SimpleMath::Vector3 boxR = b->GetSize();
	DirectX::SimpleMath::Vector3 boxP = b->GetPosition();

	float point[3] = { p.x , p.y , p.z };
	float min[3] = { boxP.x - boxR.x , boxP.y - boxR.y , boxP.z - boxR.z };
	float max[3] = { boxP.x + boxR.x , boxP.y + boxR.y , boxP.z + boxR.z };

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}
