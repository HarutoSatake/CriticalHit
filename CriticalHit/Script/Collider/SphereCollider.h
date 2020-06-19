// ‹…‘Ì‚Ì“–‚½‚è”»’è
#pragma once
#include "Collider.h"


class SphereCollider :
	public Collider
{
private:
	float m_radius;

public:
	SphereCollider(GameObject* object,float radius = 1.0f);
	~SphereCollider() = default;

public:
	float GetRadius() const;
	void SetRadius(float radius);
};

