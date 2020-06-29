#pragma once
#include "GameObject.h"

#include <GeometricPrimitive.h>

#include "SphereCollider.h"
#include "Player.h"
class ChargeShot :
	public GameObject
{
public:
	// 弾の基礎速度
	static constexpr float MOVE_BASESPEED	= 0.2f;
	// 飛距離
	static constexpr float MAXMUM_RANGE		= 20.0f;
	// チャージできる最大の威力
	static constexpr int MAXPOWER			= 5;
private:
	// モデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	// 速度
	DirectX::SimpleMath::Vector3				 m_velocity;
	// 飛距離
	float										 m_length;
	// 当たり判定
	std::unique_ptr<SphereCollider>				 m_collider;
	// 弾の威力
	float m_power;
	// 弾の速度
	float m_speed;
	// 弾の半径
	float m_radius;
	// 発射されてるかどうか
	bool m_isShot;
	// 当たった時のフラグ
	bool m_colFlag;

public:
	ChargeShot(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth,float power);
public:
	~ChargeShot();

public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
};

