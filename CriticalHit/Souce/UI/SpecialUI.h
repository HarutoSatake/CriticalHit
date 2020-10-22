#pragma once
#include "..\GameObject\GameObject.h"
class SpecialUI :
	public GameObject
{
public:
	static constexpr int SIZE_W = 140;
	static constexpr int SIZE_H = 50;

	enum IMAGE_TYPE
	{
		TYPE_FRAME = 1, // フレーム
		TYPE_FRONT,		// ゲージ表
		TYPE_BACK,		// ゲージ裏

		TYPE_SUM		// 合計数(使うときはー１すること)
	};

public:
	// コンストラクタ
	SpecialUI();
	// デストラクタ
	~SpecialUI();
public:
	// 更新処理
	void Update(float elapsedTime) override;
	// 描画処理
	void Render() override;
	// 当たり判定
	void OnCollision(GameObject* object) override;
private:
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 表示位置
	int m_x, m_y;
	// プレイヤーのチャージポイント
	float m_playerSP;

};

