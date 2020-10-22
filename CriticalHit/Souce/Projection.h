// �v���W�F�N�V�����i�ˉe)�N���X
// ���|���o


#pragma once

// �w�b�_�C���N���[�h
#include <SimpleMath.h>

// �v���W�F�N�V�����N���X
class Projection final
{
private:
	// �s��
	DirectX::SimpleMath::Matrix m_matrix;

public:
	// �R���X�g���N�^
	Projection() = default;
public:
	// �f�X�g���N�^
	~Projection() = default;

public:
	// �s����擾
	const DirectX::SimpleMath::Matrix& GetMatrix() const;
	// �ˉe�s���o�^
	void SetPerspectiveFieldOfview(float fov, float aspecRatio, float nearPlane, float farPlane);

};
// �s����擾
inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}
// �ˉe�s����擾
inline void Projection::SetPerspectiveFieldOfview(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_matrix
		= DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
}