#pragma once


#include <GeometricPrimitive.h>

#include "..\..\GameObject\GameObject.h"
#include "..\..\Collider\SphereCollider.h"

class Bullet : public GameObject
{
public:
	static constexpr float MOVE_SPEED = 0.6f;
	static constexpr float MAXMUM_RANGE = 30.0f;
	static constexpr float SERACH_RANGE = 3.0f;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	std::unique_ptr<DirectX::GeometricPrimitive> m_colliderGeometric;
	DirectX::SimpleMath::Vector3                 m_velocity;
	DirectX::SimpleMath::Vector3                 m_origin;
	float										 m_length;
	std::unique_ptr<SphereCollider>				 m_collider;
	bool										 m_colFlag;
	bool										 m_isTargeting;
	GameObject*									 m_target;


public:
	Bullet(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth);

public:
	~Bullet();


public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
};
