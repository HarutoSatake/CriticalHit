#pragma once

#include <SimpleMath.h>
#include <vector>

class Collider;
class SphereCollider;
class BoxCollider;

class CollisionManager
{
	// ���p���邽�ߊy�ɂȂ�悤��
	using ColliderList = std::vector<Collider*>;

private:
	ColliderList m_colliders;
public:
	CollisionManager();
	~CollisionManager();

public:
	void add(Collider* collider);
	void DetectCollision();

private:
	// �֐��I�[�o�[���C�h�S
	bool IsCollided(const Collider*		collider1, const Collider* collider2) const;
	bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2) const;
	bool IsCollided(const BoxCollider* collider1, const BoxCollider* collider2) const;
	bool IsCollided(const SphereCollider* collider1, const BoxCollider* collider2) const;
	bool IsCollided(const BoxCollider* collider1, const SphereCollider* collider2) const;
// �����֐�
	// �_�ƃ{�b�N�X�̊Ԃ̍ŒZ�������v�Z
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const BoxCollider* b);
	
};

