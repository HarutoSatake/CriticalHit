// �Œ�R�Â��J�����̃\�[�X
// ���|���o

// �w�b�_�C���N���[�h
#include "pch.h"
#include "FixedCamera.h"
#include "GameContext.h"

// �R���X�g���N�^
FixedCamera::FixedCamera()
{
	m_view = std::make_unique<View>();
}

// �f�X�g���N�^
FixedCamera::~FixedCamera()
{
}

// �X�V����(�R�Â���Q�[���I�u�W�F�N�g)
void FixedCamera::Update(GameObject* obj)
{
	// �r���[���W���Z�o����
	DirectX::SimpleMath::Vector3 eye(0.0f, 3.0f, 15.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 3.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_eye = eye;
	m_target = target;

	// �Z�o
	m_view->CreateLookAt(eye, target, up);

	// �Q�[���R���e�L�X�g�ɒǉ�
	GameContext<View>::Register(m_view);
}
