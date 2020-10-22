#pragma once
#include "..\GameObject\GameObject.h"
class ChargeUI :
	public GameObject
{
public:
	static constexpr int SIZE_W = 150;
	static constexpr int SIZE_H = 50;

	enum IMAGE_TYPE
	{
		TYPE_BACK = 1,	// ゲージ裏
		TYPE_FRONT,	// ゲージ表
		

		TYPE_SUM	// 合計数(使うときは－１すること)
	};


public:
	// コンストラクタ
	ChargeUI();
	// デストラクタ
	~ChargeUI();
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
	// チャージポイント
	int m_playerCP;
	// プレイヤーの二次元座標
	DirectX::SimpleMath::Vector2 m_playerPos;
};

