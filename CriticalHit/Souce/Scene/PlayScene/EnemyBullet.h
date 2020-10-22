// ìGÇÃíeÇÃÉNÉâÉXÅ@Ç‰Ç¡Ç≠ÇËÇﬂÇÃ
#pragma once
#include "..\..\GameObject\GameObject.h"

#include <GeometricPrimitive.h>
#include "..\..\Collider\SphereCollider.h"
class EnemyBullet :
	public GameObject
{
public:
	static constexpr float MOVE_SPEED = 0.1f;
	static constexpr float MAXMUM_RANGE = 30.0f;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	DirectX::SimpleMath::Vector3				 m_velocity;
	float										 m_length;
	std::unique_ptr<SphereCollider>				 m_collider;
	bool										 m_colflg;
	
public:
	EnemyBullet(const DirectX::SimpleMath::Vector3& position,const DirectX::SimpleMath::Vector3& azimuth);
	~EnemyBullet() = default;

public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
};

