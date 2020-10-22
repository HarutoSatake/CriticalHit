// �ǔ��p�J�����̃\�[�X(���g�p) 
// ���|���o

// �w�b�_�C���N���[�h
#include "..\pch.h"
#include "TargetCamera.h"
#include "..\GameContext.h"


TargetCamera::TargetCamera()
{
	// �r���[�s��쐬
	DirectX::SimpleMath::Vector3 pos(0.0f, 1.0f, 10.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);

	m_pos = pos;
	m_target = target;
	m_view = std::make_unique<View>();
	m_proj = std::make_unique<Projection>();
}


TargetCamera::~TargetCamera()
{
}
void TargetCamera::Create(DX::DeviceResources* deviceResources)
{
	// �E�B���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	// ��p��ݒ�
	float fovangleY = DirectX::XMConvertToRadians(45.0f);
	// �v���W�F�N�V�������W�쐬
	m_proj->SetPerspectiveFieldOfview(fovangleY, aspectRatio, 0.01f, 100.0f);
	// �v���W�F�N�V�������W���R���e�L�X�g�ɒǉ�
	GameContext<Projection>::Register(m_proj);
	// �r���[���W���쐬
	m_view->CreateLookAt(m_pos, m_target, up);
	// �r���[���W���R���e�L�X�g�ɒǉ�
	GameContext<View>::Register(m_view);
}
void TargetCamera::Update()
{
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_pos += (m_refEye - m_pos) * AJUST;
	m_target += (m_refTarget - m_target) * AJUST;
	
	// �N���G�C�g���_�Ńr���[���W�͏o���オ���Ă�͂�������^�]
	// �r���[���W���X�V
	GameContext<View>::Get()->CreateLookAt(m_pos, m_target, up);
}
void TargetCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_refTarget = target;
}
void TargetCamera::SetEye(DirectX::SimpleMath::Vector3 eye)
{
	m_refEye = eye;

}
DirectX::SimpleMath::Matrix TargetCamera::GetView()
{
	return m_view->GetMatrix();
}

DirectX::SimpleMath::Matrix TargetCamera::GetProj()
{
	return m_proj->GetMatrix();
}
