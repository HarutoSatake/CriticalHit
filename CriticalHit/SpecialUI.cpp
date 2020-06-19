#include "pch.h"
#include "SpecialUI.h"
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include "DeviceResources.h"
#include "ScoreManager.h"

// �R���X�g���N�^
SpecialUI::SpecialUI()
	: m_texture(nullptr),m_x(0),m_y(55)
	, m_playerSP(0)
	, GameObject("UI")
{
	// �f�o�C�X���\�[�X�擾
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	// �e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\ChargeUI.png",
		nullptr, m_texture.GetAddressOf());
}
// �f�X�g���N�^
SpecialUI::~SpecialUI()
{
}

// �X�V����
void SpecialUI::Update(float elapsedTime)
{
	m_playerSP = ScoreManager::GetInstance()->GetPlayerSP();
}

void SpecialUI::Render()
{
	// �����Q�[�W(�\)��`��
	RECT srcRect = { 0,SIZE_H * (TYPE_FRONT - 1),((int)SIZE_W * (float)(m_playerSP / 5.0f)),SIZE_H * TYPE_FRONT };
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
	// �t���[����`��
	srcRect = { 0,SIZE_H * (TYPE_FRAME - 1),SIZE_W,SIZE_H * TYPE_FRAME };
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y),&srcRect);
}

void SpecialUI::OnCollision(GameObject * object)
{
}
