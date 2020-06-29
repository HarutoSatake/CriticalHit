#include "pch.h"
#include "SpecialUI.h"
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include "DeviceResources.h"
#include "ScoreManager.h"

// コンストラクタ
SpecialUI::SpecialUI()
	: m_texture(nullptr),m_x(0),m_y(55)
	, m_playerSP(0)
	, GameObject("UI")
{
	// デバイスリソース取得
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	/*ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();*/

	// テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\ChargeUI.png",
		nullptr, m_texture.GetAddressOf());
}
// デストラクタ
SpecialUI::~SpecialUI()
{
}

// 更新処理
void SpecialUI::Update(float elapsedTime)
{
	// 不使用
	(void)elapsedTime;
	m_playerSP = static_cast<float>(ScoreManager::GetInstance()->GetPlayerSP());
}

void SpecialUI::Render()
{
	// 内部ゲージ(表)を描画
	RECT srcRect = {static_cast<LONG>(0),static_cast<LONG>(SIZE_H * (TYPE_FRONT - 1)),static_cast<LONG>(((int)SIZE_W * (float)(m_playerSP / 5.0f))),static_cast<LONG>((SIZE_H * TYPE_FRONT))};
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
	// フレームを描画
	srcRect = { 0,SIZE_H * (TYPE_FRAME - 1),SIZE_W,SIZE_H * TYPE_FRAME };
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y),&srcRect);
}

void SpecialUI::OnCollision(GameObject * object)
{
	// 不使用
	(void)object;
}

