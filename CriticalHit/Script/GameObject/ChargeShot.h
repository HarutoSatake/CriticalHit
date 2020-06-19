#pragma once
#include "GameObject.h"

#include <GeometricPrimitive.h>

#include "SphereCollider.h"
#include "Player.h"
class ChargeShot :
	public GameObject
{
public:
	// �e�̊�b���x
	static constexpr float MOVE_BASESPEED	= 0.2f;
	// �򋗗�
	static constexpr float MAXMUM_RANGE		= 20.0f;
	// �`���[�W�ł���ő�̈З�
	static constexpr int MAXPOWER			= 5;
private:
	// ���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	// ���x
	DirectX::SimpleMath::Vector3				 m_velocity;
	// �򋗗�
	float										 m_length;
	// �����蔻��
	std::unique_ptr<SphereCollider>				 m_collider;
	// �e�̈З�
	float m_power;
	// �e�̑��x
	float m_speed;
	// �e�̔��a
	float m_radius;
	// ���˂���Ă邩�ǂ���
	bool m_isShot;
	// �����������̃t���O
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

