#pragma once
#include "..\GameObject\GameObject.h"
#include <SpriteBatch.h>
class HPGauge :
	public GameObject
{
public:
	static constexpr int SIZE_W = 255;
	static constexpr int SIZE_H = 80;
	
	enum IMAGE_TYPE
	{
		TYPE_FRAME = 1,	// フレーム
		TYPE_FRONT,	// ゲージ表
		TYPE_BACK,	// ゲージ裏

		TYPE_SUM	// 合計数(使うときは－１すること)
	};


public:
	// コンストラクタ
	HPGauge();
	// デストラクタ
	~HPGauge();
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
	// プレイヤーのHP
	float m_playerHP;
};

