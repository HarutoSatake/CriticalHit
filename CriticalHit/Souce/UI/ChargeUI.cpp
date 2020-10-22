#include "..\pch.h"
#include "ChargeUI.h"
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include "..\View.h"
#include "..\DeviceResources.h"
#include "..\Manager\GameObjectManager.h"
#include "..\Manager\CollisionManager.h"
#include <Mouse.h>

ChargeUI::ChargeUI()
: m_texture(nullptr), m_x(0), m_y(0)
, m_playerPos(DirectX::SimpleMath::Vector3::Zero)
, GameObject("UI")
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	/*ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();*/

	// テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\ChargeShotUI.png",
		nullptr, m_texture.GetAddressOf());
}


ChargeUI::~ChargeUI()
{
}

void ChargeUI::Update(float elapsedTime)
{
	// 不使用
	(void)elapsedTime;
	// マウスの取得
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();

	// プレイヤーの座標取得
	std::vector<GameObject*> player = GameContext<GameObjectManager>::Get()->Find("Pointer");
	DirectX::SimpleMath::Vector3 p_pos = player.back()->GetPosition();

	// プレイヤーのチャージポイント取得
	m_playerCP = ScoreManager::GetInstance()->GetPlayerCP();

	// 三次元座標を二次元座標に変換
	m_playerPos = DirectX::SimpleMath::Vector2(p_pos.x, p_pos.y);
	m_x = mouse.x - 55;
	m_y = mouse.y - 80;
}

void ChargeUI::Render()
{

		// 内部ゲージ(裏)を描画
		RECT srcRect = { 0,SIZE_H * (TYPE_BACK - 1),SIZE_W,SIZE_H * TYPE_BACK };
		GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
		// 内部ゲージ(表)を描画
		srcRect = { 0,SIZE_H * (TYPE_FRONT - 1),(int)(SIZE_W * ((float)m_playerCP / 5.0f)),SIZE_H * TYPE_FRONT };
		GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
}

void ChargeUI::OnCollision(GameObject * object)
{
	// 不使用
	(void)object;
}

