#pragma once
#include "..\GameObject\GameObject.h"
class ChargeUI :
	public GameObject
{
public:
	static constexpr int SIZE_W = 150;
	static constexpr int SIZE_H = 50;

	enum IMAGE_TYPE
	{
		TYPE_BACK = 1,	// �Q�[�W��
		TYPE_FRONT,	// �Q�[�W�\
		

		TYPE_SUM	// ���v��(�g���Ƃ��́|�P���邱��)
	};


public:
	// �R���X�g���N�^
	ChargeUI();
	// �f�X�g���N�^
	~ChargeUI();
public:
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�揈��
	void Render() override;
	// �����蔻��
	void OnCollision(GameObject* object) override;
private:
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �\���ʒu
	int m_x, m_y;
	// �`���[�W�|�C���g
	int m_playerCP;
	// �v���C���[�̓񎟌����W
	DirectX::SimpleMath::Vector2 m_playerPos;
};

