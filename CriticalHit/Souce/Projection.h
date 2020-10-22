// プロジェクション（射影)クラス
// 佐竹晴登


#pragma once

// ヘッダインクルード
#include <SimpleMath.h>

// プロジェクションクラス
class Projection final
{
private:
	// 行列
	DirectX::SimpleMath::Matrix m_matrix;

public:
	// コンストラクタ
	Projection() = default;
public:
	// デストラクタ
	~Projection() = default;

public:
	// 行列を取得
	const DirectX::SimpleMath::Matrix& GetMatrix() const;
	// 射影行列を登録
	void SetPerspectiveFieldOfview(float fov, float aspecRatio, float nearPlane, float farPlane);

};
// 行列を取得
inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}
// 射影行列を取得
inline void Projection::SetPerspectiveFieldOfview(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_matrix
		= DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
}