// �ėp�֐��Q�̃w�b�_
// ���|���o
#pragma once

#include <algorithm>
#include <SimpleMath.h>

// �N�����v�֐�
template <class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}

// �X�N���[�����W�����[���h���W�ɕϊ�
DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
// �����ƕ��ʂ̌�_�����߂�
DirectX::SimpleMath::Vector3 SegmentWithPlaneIntersection(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Plane plane);
// Int�^�̗����𐶐�����
int RandomInt(const int& min, const int& max);
// Vector3�^�̗����𐶐�����
DirectX::SimpleMath::Vector3 RandomVector(DirectX::SimpleMath::Vector3 min,DirectX::SimpleMath::Vector3 max);
// Vector2�^�̗����𐶐�����
DirectX::SimpleMath::Vector2 RandomVector(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);
