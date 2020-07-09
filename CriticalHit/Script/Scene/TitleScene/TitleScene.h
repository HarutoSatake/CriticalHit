// タイトルシーンのヘッダ
// 佐竹晴登
#pragma once
// ヘッダインクルード
#include <SpriteBatch.h>
#include <SimpleMath.h>

#include "EffectManager.h"
#include "GameScene.h"

class TitleScene :
	public GameScene
{
public:
	TitleScene();
	~TitleScene();
	
	// 公開処理
	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float elapedTime) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
	std::unique_ptr<DirectX::SpriteBatch>				m_spriteBatch;
	DirectX::SimpleMath::Vector2						m_pos;
	float												m_wait;
	bool												m_nextscene;
	bool												m_begin;
	// 画面構成
	DirectX::SimpleMath::Vector3			m_camera;
	DirectX::SimpleMath::Matrix				m_view;
	DirectX::SimpleMath::Matrix				m_proj;
};

