// 追尾用カメラのソース(未使用) 
// 佐竹晴登

// ヘッダインクルード
#include "..\pch.h"
#include "TargetCamera.h"
#include "..\GameContext.h"


TargetCamera::TargetCamera()
{
	// ビュー行列作成
	DirectX::SimpleMath::Vector3 pos(0.0f, 1.0f, 10.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);

	m_pos = pos;
	m_target = target;
	m_view = std::make_unique<View>();
	m_proj = std::make_unique<Projection>();
}


TargetCamera::~TargetCamera()
{
}
void TargetCamera::Create(DX::DeviceResources* deviceResources)
{
	// ウィンドウサイズからアスペクト比を算出する
	RECT size = deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	// 画角を設定
	float fovangleY = DirectX::XMConvertToRadians(45.0f);
	// プロジェクション座標作成
	m_proj->SetPerspectiveFieldOfview(fovangleY, aspectRatio, 0.01f, 100.0f);
	// プロジェクション座標をコンテキストに追加
	GameContext<Projection>::Register(m_proj);
	// ビュー座標を作成
	m_view->CreateLookAt(m_pos, m_target, up);
	// ビュー座標をコンテキストに追加
	GameContext<View>::Register(m_view);
}
void TargetCamera::Update()
{
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_pos += (m_refEye - m_pos) * AJUST;
	m_target += (m_refTarget - m_target) * AJUST;
	
	// クリエイト時点でビュー座標は出来上がってるはずだから運転
	// ビュー座標を更新
	GameContext<View>::Get()->CreateLookAt(m_pos, m_target, up);
}
void TargetCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_refTarget = target;
}
void TargetCamera::SetEye(DirectX::SimpleMath::Vector3 eye)
{
	m_refEye = eye;

}
DirectX::SimpleMath::Matrix TargetCamera::GetView()
{
	return m_view->GetMatrix();
}

DirectX::SimpleMath::Matrix TargetCamera::GetProj()
{
	return m_proj->GetMatrix();
}
