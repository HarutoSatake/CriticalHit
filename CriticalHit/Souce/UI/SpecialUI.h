#pragma once
#include "..\GameObject\GameObject.h"
class SpecialUI :
	public GameObject
{
public:
	static constexpr int SIZE_W = 140;
	static constexpr int SIZE_H = 50;

	enum IMAGE_TYPE
	{
		TYPE_FRAME = 1, // �t���[��
		TYPE_FRONT,		// �Q�[�W�\
		TYPE_BACK,		// �Q�[�W��

		TYPE_SUM		// ���v��(�g���Ƃ��́[�P���邱��)
	};

public:
	// �R���X�g���N�^
	SpecialUI();
	// �f�X�g���N�^
	~SpecialUI();
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
	// �v���C���[�̃`���[�W�|�C���g
	float m_playerSP;

};

