// 固定紐づきカメラのソース
// 佐竹晴登

// ヘッダインクルード
#include "pch.h"
#include "FixedCamera.h"
#include "GameContext.h"

// コンストラクタ
FixedCamera::FixedCamera()
{
	m_view = std::make_unique<View>();
}

// デストラクタ
FixedCamera::~FixedCamera()
{
}

// 更新処理(紐づけるゲームオブジェクト)
void FixedCamera::Update(GameObject* obj)
{
	// ビュー座標を算出する
	DirectX::SimpleMath::Vector3 eye(0.0f, 3.0f, 15.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 3.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_eye = eye;
	m_target = target;

	// 算出
	m_view->CreateLookAt(eye, target, up);

	// ゲームコンテキストに追加
	GameContext<View>::Register(m_view);
}
