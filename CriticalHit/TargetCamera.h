// カメラクラスのヘッダ

// 多重インクルード防止
#pragma once
// インクルード
#include <SimpleMath.h>
#include "DeviceResources.h"
#include "View.h"
#include "Projection.h"
// カメラクラス
class TargetCamera
{
public:
	// 定数
	static constexpr DirectX::SimpleMath::Vector3 EYE = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f);
	static constexpr float AJUST = 0.1f;
public:
	TargetCamera();
	~TargetCamera();
	void Create(DX::DeviceResources* deviceResources);
	void Update();
	void SetTarget(DirectX::SimpleMath::Vector3 target);
	void SetEye(DirectX::SimpleMath::Vector3 eye);
	DirectX::SimpleMath::Matrix GetView();
	DirectX::SimpleMath::Matrix GetProj();
private:
	// ビュー座標
	std::unique_ptr<View> m_view;
	// プロジェクション座標
	std::unique_ptr<Projection> m_proj;
	// カメラの位置
	DirectX::SimpleMath::Vector3 m_pos;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// 参照視点
	DirectX::SimpleMath::Vector3 m_refEye;
	// 参照注視点
	DirectX::SimpleMath::Vector3 m_refTarget;
};

