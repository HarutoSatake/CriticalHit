// 汎用関数群のソース
// 佐竹晴登

// ヘッダインクルード
#include "pch.h"
#include <random>
#include "Utilities.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 処理　：ワールド座標をスクリーン座標に変換する変数
// 引数　：スクリーンの横幅、スクリーンの縦幅、ビュー行列、射影行列
// 戻り値：Matrix
DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	// ビューポートスケーリング行列を作成
	Matrix viewport;
	viewport._11 = screen_w / 2.0f;
	viewport._22 = -screen_h / 2.0f;
	viewport._41 = screen_w / 2.0f;
	viewport._42 = screen_h / 2.0f;

	// 逆行列を作成
	Matrix invS = viewport.Invert();
	Matrix invP = projection.Invert();
	Matrix invV = view.Invert();

	// 計算
	return invS * invP * invV;
}
// 処理　：線分と平面の交点を求める
// 引数　：始端座標、終端座標、Plane要素
// 戻り値：Vector3
DirectX::SimpleMath::Vector3 SegmentWithPlaneIntersection(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Plane plane)
{

	// 平面上の点P
	Vector3 P = Vector3(plane.x * plane.w, plane.y * plane.w, plane.z * plane.w);

	// PS PEベクトル
	Vector3 PS = Vector3(P.x - start.x, P.y - start.y, P.z - start.z);
	Vector3 PE = Vector3(P.x - end.x, P.y - end.y, P.z - end.z);

	// PS PEの平面法線と内積
	float dot_PS = PS.x * plane.x + PS.y * plane.y + PS.z * plane.z;
	float dot_PE = PE.x * plane.x + PE.y * plane.y + PE.z * plane.z;
	
	// 先端が平面上にあった際の誤差の調整
	if (abs(dot_PS) < 0.000001) {	dot_PS = 0.0; }
	if (abs(dot_PE) < 0.000001) {	dot_PE = 0.0; }

	// 平面上の交点を求める
	Vector3 SE = Vector3(end.x - start.x, end.y - start.y, end.z - start.z);

	// 交点とSの距離　:　交点とEの距離　= dot_PA : dot_PB
	float ratio = abs(dot_PS) / (abs(dot_PS) + abs(dot_PE));

	// 交点を算出
	Vector3 intersection = Vector3(
		start.x + (SE.x * ratio),
		start.y + (SE.y * ratio),
		start.z + (SE.z * ratio)
	);

	return intersection;
}
// 処理　：int型の乱数生成
// 引数　：最低の数値、最大の数値
// 戻り値：int
int RandomInt(const int& min, const int& max)
{
	// 非決定な乱数生成器
	std::random_device seed_gen;
	// ランダムなシードを設定する
	std::mt19937 engine(seed_gen());
	// 分布方法
	std::uniform_int_distribution<> dist(min,max);

	// 乱数生成
	int result = dist(engine);

	return result;
}
// 処理　：Vector3型の乱数生成
// 引数　：最低の数値、最大の数値
// 戻り値：Vector3
DirectX::SimpleMath::Vector3 RandomVector(DirectX::SimpleMath::Vector3 min, DirectX::SimpleMath::Vector3 max)
{
	// 各要素に乱数を設定
	float x = static_cast<float>(RandomInt(static_cast<int>(min.x), static_cast<int>(max.x)));
	float y = static_cast<float>(RandomInt(static_cast<int>(min.y), static_cast<int>(max.y)));
	float z = static_cast<float>(RandomInt(static_cast<int>(min.z), static_cast<int>(max.y)));
	
	DirectX::SimpleMath::Vector3 vec(x, y, z);

	return vec;
}
// 処理　：Vector2型の乱数生成
// 引数　：最低の数値、最大の数値
// 戻り値：Vector2
DirectX::SimpleMath::Vector2 RandomVector(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
{
	// 各要素に乱数を設定
	float x = static_cast<float>(RandomInt(static_cast<int>(min.x), static_cast<int>(max.x)));
	float y = static_cast<float>(RandomInt(static_cast<int>(min.y), static_cast<int>(max.y)));

	DirectX::SimpleMath::Vector2 vec(x, y);

	return vec;
}
