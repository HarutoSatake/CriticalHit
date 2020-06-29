#pragma once


#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Model.h>

#include "GameObject.h"
#include "BoxCollider.h"

class Player : public GameObject
{
public:
	enum STATE
	{
		DEMO_STATE,			// デモシーン
		NORMAL_STATE,		// 基本
		CHARGE_STATE,		// チャージ中
		SPECIAL_STATE,		// スペシャル(現状乱射)
		DESTROY_STATE,		// 破壊された
		CLEAR_STATE,		// クリア

		SUM_STATE
	};
	enum SHOT_TYPE
	{
		NORMAL_TYPE,
		CHARGE_TYPE,
		SPECIAL_TYPE,

		SUM_TYPE
	};
public:
	// 移動速度
	static constexpr float MOVE_SPEED = 0.1f;
	// 回転速度
	static constexpr float ANGULAR_SPEED = 2.0f;
	// 注視点
	static constexpr DirectX::SimpleMath::Vector3 BASE_VEC = DirectX::SimpleMath::Vector3(0.0f, 3.0f, 5.0f);
	// 限界距離
	static constexpr float MAX_LENGTH = 10.0f;
	// プレイヤーの最大HP
	static constexpr int	MAX_HP = 5;


private:
	// ステート
	STATE														m_state;
	// ジオメトリプリミティブ
	std::unique_ptr<DirectX::GeometricPrimitive>				m_pGeometricPrimitive;
	// モデル
	std::unique_ptr<DirectX::Model>								m_pModel;
	// コライダー
	std::unique_ptr<BoxCollider>								m_collider;
	// 当たったかのフラグ
	bool														m_colFlag;
	// マウストラッカー
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_pMouseTracker;
	// 速度
	DirectX::SimpleMath::Vector3								m_velocity;
	float														m_horizontalAngle;
	float														m_fireInterval;
	float														m_elapsedTime;
	// ショット
	bool														m_isLoading;
	// チャージショットの威力
	float														m_shotPower;
	// チャージの間隔
	float														m_chargeInterval;
	// レーザーのチャージポイント
	int															m_laserPoint;
	// レーザーの発動回数
	int															m_laserCount;
	// スコアを保存
	int															m_lastScore;
	// プレイヤーのHP
	int															m_hp;
public:
	// コンストラクタ
	Player(const DirectX::SimpleMath::Vector3& position, float fireInterval);
public:
	// デストラクタ
	~Player();
public:
	// 更新処理
	void Update(float elapsedTime) override;
	 // 描画処理
	void Render() override;
	// 当たり判定処理
	void OnCollision(GameObject* object) override;
private:
	// 更新処理(デモ)
	void DemoState(float elapsedTime);
	// 更新処理(基本)
	void NormalState(float elapsedTime);
	// 更新処理(チャージ中)
	void ChargeState(float elapsedtime);
	// 更新処理(必殺)
	void SpecioalState(float elapsedTime);
	// 更新処理(破壊された)
	void DestroyState(float elapsedTime);
	// 更新処理(クリア)
	void ClearState(float elapsedTime);
	// 移動処理
	void Move(float elapsedtime);
	// 射撃処理
	void Shot(const int& shottype = SHOT_TYPE::NORMAL_TYPE);
};
