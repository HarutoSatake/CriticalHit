// ���U���g�V�[���̃\�[�X

#pragma once

// �w�b�_�C���N���[�h
#include "..\..\GameScene.h"
#include "..\..\UI\Font.h"

class ResultScene :
	public GameScene
{
// ���J����
public:
	// �R���X�g���N�^
	ResultScene();
	// �f�X�g���N�^
	~ResultScene();
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapedTime) override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;
private:
	// �ŏI�X�R�A
	int m_score;
	// �w�i�i���摜�j�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_BG_BACKTexture;
	// �w�i�i��摜�j�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_BG_FRONTTexture;
	// �����e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mojiTexture;
	// �����N���X
	Moji m_ScoreMoji;
	
	float m_wait;
	
	bool m_begin;

	bool m_nextscene;
	// ��ʍ\��
	DirectX::SimpleMath::Vector3			m_camera;
	DirectX::SimpleMath::Matrix				m_view;
	DirectX::SimpleMath::Matrix				m_proj;
};

