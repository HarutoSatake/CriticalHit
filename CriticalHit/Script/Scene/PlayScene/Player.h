#pragma once


#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Model.h>

#include "GameObject.h"
#include "BoxCollider.h"

class Player : public GameObject
{
public:
	enum STATE
	{
		DEMO_STATE,			// �f���V�[��
		NORMAL_STATE,		// ��{
		CHARGE_STATE,		// �`���[�W��
		SPECIAL_STATE,		// �X�y�V����(���󗐎�)
		DESTROY_STATE,		// �j�󂳂ꂽ
		CLEAR_STATE,		// �N���A

		SUM_STATE
	};
	enum SHOT_TYPE
	{
		NORMAL_TYPE,
		CHARGE_TYPE,
		SPECIAL_TYPE,

		SUM_TYPE
	};
public:
	// �ړ����x
	static constexpr float MOVE_SPEED = 0.1f;
	// ��]���x
	static constexpr float ANGULAR_SPEED = 2.0f;
	// �����_
	static constexpr DirectX::SimpleMath::Vector3 BASE_VEC = DirectX::SimpleMath::Vector3(0.0f, 3.0f, 5.0f);
	// ���E����
	static constexpr float MAX_LENGTH = 10.0f;
	// �v���C���[�̍ő�HP
	static constexpr int	MAX_HP = 5;


private:
	// �X�e�[�g
	STATE														m_state;
	// �W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive>				m_pGeometricPrimitive;
	// ���f��
	std::unique_ptr<DirectX::Model>								m_pModel;
	// �R���C�_�[
	std::unique_ptr<BoxCollider>								m_collider;
	// �����������̃t���O
	bool														m_colFlag;
	// �}�E�X�g���b�J�[
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_pMouseTracker;
	// ���x
	DirectX::SimpleMath::Vector3								m_velocity;
	float														m_horizontalAngle;
	float														m_fireInterval;
	float														m_elapsedTime;
	// �V���b�g
	bool														m_isLoading;
	// �`���[�W�V���b�g�̈З�
	float														m_shotPower;
	// �`���[�W�̊Ԋu
	float														m_chargeInterval;
	// ���[�U�[�̃`���[�W�|�C���g
	int															m_laserPoint;
	// ���[�U�[�̔�����
	int															m_laserCount;
	// �X�R�A��ۑ�
	int															m_lastScore;
	// �v���C���[��HP
	int															m_hp;
public:
	// �R���X�g���N�^
	Player(const DirectX::SimpleMath::Vector3& position, float fireInterval);
public:
	// �f�X�g���N�^
	~Player();
public:
	// �X�V����
	void Update(float elapsedTime) override;
	 // �`�揈��
	void Render() override;
	// �����蔻�菈��
	void OnCollision(GameObject* object) override;
private:
	// �X�V����(�f��)
	void DemoState(float elapsedTime);
	// �X�V����(��{)
	void NormalState(float elapsedTime);
	// �X�V����(�`���[�W��)
	void ChargeState(float elapsedtime);
	// �X�V����(�K�E)
	void SpecioalState(float elapsedTime);
	// �X�V����(�j�󂳂ꂽ)
	void DestroyState(float elapsedTime);
	// �X�V����(�N���A)
	void ClearState(float elapsedTime);
	// �ړ�����
	void Move(float elapsedtime);
	// �ˌ�����
	void Shot(const int& shottype = SHOT_TYPE::NORMAL_TYPE);
};
