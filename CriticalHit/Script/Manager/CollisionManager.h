#pragma once

#include <SimpleMath.h>
#include <vector>

class Collider;
class SphereCollider;
class BoxCollider;

class CollisionManager
{
	// 多用するため楽になるように
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
	// 関数オーバーライド郡
	bool IsCollided(const Collider*		collider1, const Collider* collider2) const;
	bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2) const;
	bool IsCollided(const BoxCollider* collider1, const BoxCollider* collider2) const;
	bool IsCollided(const SphereCollider* collider1, const BoxCollider* collider2) const;
	bool IsCollided(const BoxCollider* collider1, const SphereCollider* collider2) const;
// 内部関数
	// 点とボックスの間の最短距離を計算
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const BoxCollider* b);
	
};

