// �Œ�R�Â��J�����̃w�b�_
// ���|���o

#pragma once

// �w�b�_�C���N���[�h
#include <SimpleMath.h>
#include "View.h"
#include "Projection.h"
#include "GameObject.h"

// �Œ�J�����N���X
class FixedCamera
{
// �萔
public:
	static constexpr float DEFAULT_CAMERA_DISTANCE = 5.0f;
// �ϐ�
private:
	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �r���[���W
	std::unique_ptr<View> m_view;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	
// �A�N�Z�b�T
public: 


	// �f�o�b�O�J�����̈ʒu�擾
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}
	// �f�o�b�O�J�����̒����_�擾
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}

public:
	// �R���X�g���N�^
	FixedCamera();
	// �f�X�g���N�^
	~FixedCamera();

	// �X�V����(�R�Â���Q�[���I�u�W�F�N�g)
	void Update(GameObject* obj = nullptr);
};

