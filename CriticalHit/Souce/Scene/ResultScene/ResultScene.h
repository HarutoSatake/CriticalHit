// リザルトシーンのソース

#pragma once

// ヘッダインクルード
#include "..\..\GameScene.h"
#include "..\..\UI\Font.h"

class ResultScene :
	public GameScene
{
// 公開処理
public:
	// コンストラクタ
	ResultScene();
	// デストラクタ
	~ResultScene();
	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float elapedTime) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;
private:
	// 最終スコア
	int m_score;
	// 背景（下画像）テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_BG_BACKTexture;
	// 背景（上画像）テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_BG_FRONTTexture;
	// 文字テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mojiTexture;
	// 文字クラス
	Moji m_ScoreMoji;
	
	float m_wait;
	
	bool m_begin;

	bool m_nextscene;
	// 画面構成
	DirectX::SimpleMath::Vector3			m_camera;
	DirectX::SimpleMath::Matrix				m_view;
	DirectX::SimpleMath::Matrix				m_proj;
};

