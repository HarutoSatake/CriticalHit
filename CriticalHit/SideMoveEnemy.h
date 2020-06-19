// 縦横に反復移動するエネミーさん
#pragma once
#include <GeometricPrimitive.h>

#include "GameObject.h"
#include "BoxCollider.h"
#include <Model.h>

class SideMoveEnemy :
	public GameObject
{
public:
	static constexpr float BULLET_INTERVAL = 2.0f;
public:
	// コンストラクタ(初期座標,識別（0.縦,1.横）
	SideMoveEnemy(const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),int type = 0);
	// デストラクタ
	~SideMoveEnemy() = default;
	// 更新処理（前フレームからの経過時間）
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
private:
	DirectX::SimpleMath::Vector3 m_velocity;
	// ジオメトリ
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<DirectX::GeometricPrimitive> m_colliderGeometric;
	std::unique_ptr<BoxCollider> m_collider;

	// 体力
	float m_hitPoint;
	// エネミーのプレイヤーに対するダメージ量
	int m_power;
	// 経過時間
	float m_time;
	// インターバル用カウント
	float m_count;
	// 待機時間
	float m_wait;
	// 種類(0.縦　1.横）
	int m_type;
	// 撃墜されたか否か「
	bool m_isDown;
};

