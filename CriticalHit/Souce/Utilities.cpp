// �ėp�֐��Q�̃\�[�X
// ���|���o

// �w�b�_�C���N���[�h
#include "pch.h"
#include <random>
#include "Utilities.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �����@�F���[���h���W���X�N���[�����W�ɕϊ�����ϐ�
// �����@�F�X�N���[���̉����A�X�N���[���̏c���A�r���[�s��A�ˉe�s��
// �߂�l�FMatrix
DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	// �r���[�|�[�g�X�P�[�����O�s����쐬
	Matrix viewport;
	viewport._11 = screen_w / 2.0f;
	viewport._22 = -screen_h / 2.0f;
	viewport._41 = screen_w / 2.0f;
	viewport._42 = screen_h / 2.0f;

	// �t�s����쐬
	Matrix invS = viewport.Invert();
	Matrix invP = projection.Invert();
	Matrix invV = view.Invert();

	// �v�Z
	return invS * invP * invV;
}
// �����@�F�����ƕ��ʂ̌�_�����߂�
// �����@�F�n�[���W�A�I�[���W�APlane�v�f
// �߂�l�FVector3
DirectX::SimpleMath::Vector3 SegmentWithPlaneIntersection(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Plane plane)
{

	// ���ʏ�̓_P
	Vector3 P = Vector3(plane.x * plane.w, plane.y * plane.w, plane.z * plane.w);

	// PS PE�x�N�g��
	Vector3 PS = Vector3(P.x - start.x, P.y - start.y, P.z - start.z);
	Vector3 PE = Vector3(P.x - end.x, P.y - end.y, P.z - end.z);

	// PS PE�̕��ʖ@���Ɠ���
	float dot_PS = PS.x * plane.x + PS.y * plane.y + PS.z * plane.z;
	float dot_PE = PE.x * plane.x + PE.y * plane.y + PE.z * plane.z;
	
	// ��[�����ʏ�ɂ������ۂ̌덷�̒���
	if (abs(dot_PS) < 0.000001) {	dot_PS = 0.0; }
	if (abs(dot_PE) < 0.000001) {	dot_PE = 0.0; }

	// ���ʏ�̌�_�����߂�
	Vector3 SE = Vector3(end.x - start.x, end.y - start.y, end.z - start.z);

	// ��_��S�̋����@:�@��_��E�̋����@= dot_PA : dot_PB
	float ratio = abs(dot_PS) / (abs(dot_PS) + abs(dot_PE));

	// ��_���Z�o
	Vector3 intersection = Vector3(
		start.x + (SE.x * ratio),
		start.y + (SE.y * ratio),
		start.z + (SE.z * ratio)
	);

	return intersection;
}
// �����@�Fint�^�̗�������
// �����@�F�Œ�̐��l�A�ő�̐��l
// �߂�l�Fint
int RandomInt(const int& min, const int& max)
{
	// �񌈒�ȗ���������
	std::random_device seed_gen;
	// �����_���ȃV�[�h��ݒ肷��
	std::mt19937 engine(seed_gen());
	// ���z���@
	std::uniform_int_distribution<> dist(min,max);

	// ��������
	int result = dist(engine);

	return result;
}
// �����@�FVector3�^�̗�������
// �����@�F�Œ�̐��l�A�ő�̐��l
// �߂�l�FVector3
DirectX::SimpleMath::Vector3 RandomVector(DirectX::SimpleMath::Vector3 min, DirectX::SimpleMath::Vector3 max)
{
	// �e�v�f�ɗ�����ݒ�
	float x = static_cast<float>(RandomInt(static_cast<int>(min.x), static_cast<int>(max.x)));
	float y = static_cast<float>(RandomInt(static_cast<int>(min.y), static_cast<int>(max.y)));
	float z = static_cast<float>(RandomInt(static_cast<int>(min.z), static_cast<int>(max.y)));
	
	DirectX::SimpleMath::Vector3 vec(x, y, z);

	return vec;
}
// �����@�FVector2�^�̗�������
// �����@�F�Œ�̐��l�A�ő�̐��l
// �߂�l�FVector2
DirectX::SimpleMath::Vector2 RandomVector(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
{
	// �e�v�f�ɗ�����ݒ�
	float x = static_cast<float>(RandomInt(static_cast<int>(min.x), static_cast<int>(max.x)));
	float y = static_cast<float>(RandomInt(static_cast<int>(min.y), static_cast<int>(max.y)));

	DirectX::SimpleMath::Vector2 vec(x, y);

	return vec;
}
