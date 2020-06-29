#include "pch.h"
#include "HPGauge.h"
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include "DeviceResources.h"
#include "ScoreManager.h"
// コンストラクタ
HPGauge::HPGauge()
	: m_texture(nullptr),m_x(0),m_y(0)
	, m_playerHP(0)
	, GameObject("UI")
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	/*ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();*/
	
	// テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\HPGauge.png",
		nullptr, m_texture.GetAddressOf());
}

// デストラクタ
HPGauge::~HPGauge()
{
}
// 更新処理
void HPGauge::Update(float elapsedTime)
{
	// 不使用
	(void)elapsedTime;
	// スコアマネージャーからHPを取得
	m_playerHP = static_cast<float>(ScoreManager::GetInstance()->GetPlayerHP());
}

// 描画処理
void HPGauge::Render()
{
	// 内部ゲージ(表)を描画
	RECT srcRect = { 0,SIZE_H * 2,SIZE_W,SIZE_H * TYPE_BACK};
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
	// 内部ゲージ(表)を描画
	srcRect = { 0,SIZE_H,(int)(SIZE_W * ((float)m_playerHP / 5.0f)) ,SIZE_H * TYPE_FRONT};
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
	// 切り取り
	srcRect = { 0,0,SIZE_W,SIZE_H * TYPE_FRAME };
	// フレームを描画する
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x,(float)m_y),&srcRect);
}

void HPGauge::OnCollision(GameObject * object)
{
	// 不使用
	(void)object;
}
