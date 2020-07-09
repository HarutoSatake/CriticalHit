// �^�C�g���V�[���̃w�b�_
// ���|���o
#pragma once
// �w�b�_�C���N���[�h
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
	
	// ���J����
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapedTime) override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
	std::unique_ptr<DirectX::SpriteBatch>				m_spriteBatch;
	DirectX::SimpleMath::Vector2						m_pos;
	float												m_wait;
	bool												m_nextscene;
	bool												m_begin;
	// ��ʍ\��
	DirectX::SimpleMath::Vector3			m_camera;
	DirectX::SimpleMath::Matrix				m_view;
	DirectX::SimpleMath::Matrix				m_proj;
};

