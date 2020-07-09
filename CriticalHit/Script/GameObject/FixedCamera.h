// 固定紐づきカメラのヘッダ
// 佐竹晴登

#pragma once

// ヘッダインクルード
#include <SimpleMath.h>
#include "View.h"
#include "Projection.h"
#include "GameObject.h"

// 固定カメラクラス
class FixedCamera
{
// 定数
public:
	static constexpr float DEFAULT_CAMERA_DISTANCE = 5.0f;
// 変数
private:
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// ビュー座標
	std::unique_ptr<View> m_view;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	
// アクセッサ
public: 


	// デバッグカメラの位置取得
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}
	// デバッグカメラの注視点取得
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}

public:
	// コンストラクタ
	FixedCamera();
	// デストラクタ
	~FixedCamera();

	// 更新処理(紐づけるゲームオブジェクト)
	void Update(GameObject* obj = nullptr);
};

