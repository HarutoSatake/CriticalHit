// 汎用関数群のヘッダ
// 佐竹晴登
#pragma once

#include <algorithm>
#include <SimpleMath.h>

// クランプ関数
template <class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}

// スクリーン座標をワールド座標に変換
DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
// 線分と平面の交点を求める
DirectX::SimpleMath::Vector3 SegmentWithPlaneIntersection(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Plane plane);
// Int型の乱数を生成する
int RandomInt(const int& min, const int& max);
// Vector3型の乱数を生成する
DirectX::SimpleMath::Vector3 RandomVector(DirectX::SimpleMath::Vector3 min,DirectX::SimpleMath::Vector3 max);
// Vector2型の乱数を生成する
DirectX::SimpleMath::Vector2 RandomVector(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);
