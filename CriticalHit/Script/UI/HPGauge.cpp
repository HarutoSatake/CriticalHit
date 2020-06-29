#include "pch.h"
#include "HPGauge.h"
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include "DeviceResources.h"
#include "ScoreManager.h"
// �R���X�g���N�^
HPGauge::HPGauge()
	: m_texture(nullptr),m_x(0),m_y(0)
	, m_playerHP(0)
	, GameObject("UI")
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	/*ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();*/
	
	// �e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\HPGauge.png",
		nullptr, m_texture.GetAddressOf());
}

// �f�X�g���N�^
HPGauge::~HPGauge()
{
}
// �X�V����
void HPGauge::Update(float elapsedTime)
{
	// �s�g�p
	(void)elapsedTime;
	// �X�R�A�}�l�[�W���[����HP���擾
	m_playerHP = static_cast<float>(ScoreManager::GetInstance()->GetPlayerHP());
}

// �`�揈��
void HPGauge::Render()
{
	// �����Q�[�W(�\)��`��
	RECT srcRect = { 0,SIZE_H * 2,SIZE_W,SIZE_H * TYPE_BACK};
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
	// �����Q�[�W(�\)��`��
	srcRect = { 0,SIZE_H,(int)(SIZE_W * ((float)m_playerHP / 5.0f)) ,SIZE_H * TYPE_FRONT};
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x, (float)m_y), &srcRect);
	// �؂���
	srcRect = { 0,0,SIZE_W,SIZE_H * TYPE_FRAME };
	// �t���[����`�悷��
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2((float)m_x,(float)m_y),&srcRect);
}

void HPGauge::OnCollision(GameObject * object)
{
	// �s�g�p
	(void)object;
}
