#pragma once
#include <GeometricPrimitive.h>
#include <Model.h>
#include "..\..\GameObject\GameObject.h"
#include "..\..\Collider\BoxCollider.h"

class NormalEnemy :
	public GameObject
{
public:
	static constexpr float BULLET_INTERVAL = 2.0f;
public:
	NormalEnemy(const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	~NormalEnemy();
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
private:
	DirectX::SimpleMath::Vector3 m_velocity;
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	std::unique_ptr<DirectX::Model>				 m_model;
	std::unique_ptr<DirectX::GeometricPrimitive> m_colliderGeometric;
	std::unique_ptr<BoxCollider> m_collider;
	
	// 体力
	float m_hitPoint;
	// エネミーのプレイヤーに対するダメージ量
	int m_power;
	// 経過時間
	float m_count;
	// 撃墜されたかどうか
	bool m_isDown;
};

