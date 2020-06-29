// �c���ɔ����ړ�����G�l�~�[����
#pragma once
#include <GeometricPrimitive.h>

#include "GameObject.h"
#include "BoxCollider.h"
#include <Model.h>

class SideMoveEnemy :
	public GameObject
{
public:
	static constexpr float BULLET_INTERVAL = 2.0f;
public:
	// �R���X�g���N�^(�������W,���ʁi0.�c,1.���j
	SideMoveEnemy(const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),int type = 0);
	// �f�X�g���N�^
	~SideMoveEnemy() = default;
	// �X�V�����i�O�t���[������̌o�ߎ��ԁj
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
private:
	DirectX::SimpleMath::Vector3 m_velocity;
	// �W�I���g��
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

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
	// �ҋ@����
	float m_wait;
	// ���(0.�c�@1.���j
	int m_type;
	// ���Ă��ꂽ���ۂ��u
	bool m_isDown;
};

