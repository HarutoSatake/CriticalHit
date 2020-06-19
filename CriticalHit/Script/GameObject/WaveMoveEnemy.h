#pragma once
#include <GeometricPrimitive.h>
#include <Model.h>
#include "GameObject.h"
#include "BoxCollider.h"
class WaveMoveEnemy :
	public GameObject
{
public:
	static constexpr float BULLET_INTERVAL = 1.5f;
public:
	WaveMoveEnemy(const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f));
	~WaveMoveEnemy();
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
private:
	DirectX::SimpleMath::Vector3 m_velocity;
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	std::unique_ptr<DirectX::Model>				 m_model;
	std::unique_ptr<DirectX::GeometricPrimitive> m_colliderGeometric;
	std::unique_ptr<BoxCollider> m_collider;
	
	// �̗�
	float m_hitPoint;
	// �G�l�~�[�̃v���C���[�ɑ΂���_���[�W��
	int m_power;
	// �o�ߎ���
	float m_time;
	// �C���^�[�o���p�J�E���g
	float m_count;
	// ���Ă��ꂽ���ǂ���
	bool m_isDown;
};

