// �J�����N���X�̃w�b�_

// ���d�C���N���[�h�h�~
#pragma once
// �C���N���[�h
#include <SimpleMath.h>
#include "DeviceResources.h"
#include "View.h"
#include "Projection.h"
// �J�����N���X
class TargetCamera
{
public:
	// �萔
	static constexpr DirectX::SimpleMath::Vector3 EYE = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f);
	static constexpr float AJUST = 0.1f;
public:
	TargetCamera();
	~TargetCamera();
	void Create(DX::DeviceResources* deviceResources);
	void Update();
	void SetTarget(DirectX::SimpleMath::Vector3 target);
	void SetEye(DirectX::SimpleMath::Vector3 eye);
	DirectX::SimpleMath::Matrix GetView();
	DirectX::SimpleMath::Matrix GetProj();
private:
	// �r���[���W
	std::unique_ptr<View> m_view;
	// �v���W�F�N�V�������W
	std::unique_ptr<Projection> m_proj;
	// �J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_pos;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// �Q�Ǝ��_
	DirectX::SimpleMath::Vector3 m_refEye;
	// �Q�ƒ����_
	DirectX::SimpleMath::Vector3 m_refTarget;
};

