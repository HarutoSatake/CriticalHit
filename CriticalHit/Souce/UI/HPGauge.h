#pragma once
#include "..\GameObject\GameObject.h"
#include <SpriteBatch.h>
class HPGauge :
	public GameObject
{
public:
	static constexpr int SIZE_W = 255;
	static constexpr int SIZE_H = 80;
	
	enum IMAGE_TYPE
	{
		TYPE_FRAME = 1,	// �t���[��
		TYPE_FRONT,	// �Q�[�W�\
		TYPE_BACK,	// �Q�[�W��

		TYPE_SUM	// ���v��(�g���Ƃ��́|�P���邱��)
	};


public:
	// �R���X�g���N�^
	HPGauge();
	// �f�X�g���N�^
	~HPGauge();
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
	// �v���C���[��HP
	float m_playerHP;
};

