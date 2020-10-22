// �Q�[���I�u�W�F�N�g�̊��N���X�̃w�b�_
// ���|���o

#pragma once

// �w�b�_�C���N���[�h
#include <SimpleMath.h>
#include <string>
#include "..\GameContext.h"
#include "..\Projection.h"
#include "..\DebugMode.h"

// �Q�[���I�u�W�F�N�g�N���X
class GameObject
{
private:
	bool m_isValid;


protected:
	DirectX::SimpleMath::Vector3 m_position;	// ���W
	DirectX::SimpleMath::Vector3 m_rotation;	// ��]
	DirectX::SimpleMath::Vector3 m_scale;		// �傫��
	std::string					 m_tag;			// �^�O
	bool						 m_debugMode;	// �f�o�b�O���[�h���ۂ�

public:
	// �R���X�g���N�^
	GameObject(const std::string& tag = "GameObject");
public:
	// �f�X�g���N�^
	virtual ~GameObject() = default;

// ���J����
public:
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�揈��
	virtual void Render() = 0;
	// �����蔻�菈��
	virtual void OnCollision(GameObject* object) = 0;
// �Q�b�^�ƃZ�b�^
public:
	// ��\���ɂ���
	void Invalidate();
	// �\������
	bool IsValid() const;
	// ��\���ɂ���
	bool IsInvalid() const;

	// ���݂̃^�O���擾
	const std::string& GetTag() const;
	// ���݂̍��W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	// ���݂̉�]�l���擾
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	// ���݂̑傫�����擾
	const DirectX::SimpleMath::Vector3& GetScale() const;

	// ���ݍ��W��ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3& position);
	// ���݂̉�]�l��ݒ�
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	// ���݂̑傫����ݒ�
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	// ���݂̃f�o�b�O���[�h���ۂ���ݒ�
	void SetDebugMode(const bool& value);
// �ėp�֐�
public:
	// �ړI�n�܂œ��������ړ�(�ړ�������������true��Ԃ�)
	// ����(Vector3 �ړI�n���W�Afloat �ړ����鑬�x)
	bool Translate(const DirectX::SimpleMath::Vector3& dest,const float& speed);
	// �ړI�̒l�܂œ����ŉ�]����(��]������������true��Ԃ�)
	// ����(Vector3 �ړI��]�l float ��]���x)
	bool Rotation(const DirectX::SimpleMath::Vector3& angle, const float& speed);


public:
	// �Q�[���I�u�W�F�N�g���폜����
	// ����(�폜����I�u�W�F�N�g)
	static void Destroy(GameObject* object);
};
// �\���ɂ���
inline bool GameObject::IsValid() const
{
	return m_isValid;
}
// ��\���ɂ���
inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}
// ���݂̍��W���擾
inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}
// ���݂̉�]�l���擾
inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}
// ���݂̑傫�����擾
inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}
// ���݂̃^�O���擾
inline const std::string & GameObject::GetTag() const
{
	return m_tag;
}
// ���݂̍��W��ݒ�
inline void GameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}
// ���݂̉�]�l��ݒ�
inline void GameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}
// ���݂̑傫����ݒ�
inline void GameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}
// �Q�[���I�u�W�F�N�g���폜����
inline void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}
// �f�o�b�O���[�h��ݒ�
inline void GameObject::SetDebugMode(const bool& value)
{
	m_debugMode = value;
}