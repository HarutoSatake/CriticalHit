// �t�H���g�N���X�̃w�b�_

// ���d�C���N���[�h�h�~
#pragma once

#include <SimpleMath.h>

#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <list>
#include <memory>
struct TextData
{
	wchar_t*								name;
	wchar_t*								string;
	DirectX::SimpleMath::Vector2			pos;
};
// Font�N���X
class Font
{
public:
	// �������ő�T�C�Y
	static constexpr size_t STRINGSIZE_MAX = 256;
private:
	Font();
public:
	~Font();
	// ����
	void Create(ID3D11Device* device,ID3D11DeviceContext1* context);
	// �`��
	void Render();
	// ���Z�b�g
	void reset();
	// �\�����o�^
	bool Print(wchar_t* name, float posX, float posY, wchar_t const* const format, ...);
	bool Print(wchar_t* name, DirectX::SimpleMath::Vector2 m_pos, wchar_t const* const format, ...);

public:
	// �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
	static Font* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// �I�u�W�F�N�g�𐶐����āA�|�C���^���i�[
			m_pInstance.reset(new Font());
		}
		// �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_pInstance.get();
	}
private:
	static std::unique_ptr<Font> m_pInstance;

// �����o�ϐ�
private:
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;
	std::list<TextData>						m_data;
};

