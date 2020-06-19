// �t�H���g�N���X�̃\�[�X

// �w�b�_�C���N���[�h
#include "pch.h"
#include "Font.h"

std::unique_ptr<Font> Font::m_pInstance = nullptr;

Font::Font()
{
	for (TextData& data : m_data)
	{
		data.name = new wchar_t[STRINGSIZE_MAX];
		data.pos = DirectX::SimpleMath::Vector2(0, 0);
		data.string = new wchar_t[STRINGSIZE_MAX];
	}
}


Font::~Font()
{
	
}

// ����
void Font::Create(ID3D11Device* device, ID3D11DeviceContext1* context)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources\\Debug\\logofont.spritefont");
}

// �`��
void Font::Render()
{
	m_spriteBatch->Begin();
	for (TextData& data : m_data)
	{
		m_spriteFont->DrawString(m_spriteBatch.get(), data.string, data.pos);
	}
	m_spriteBatch->End();
}
// �v�f���N���A����
void Font::reset()
{
	m_data.clear();
}
// �\�����ǉ�
bool Font::Print(wchar_t* name, float posX, float posY, wchar_t const * const format, ...)
{
	for (TextData& data : m_data)
	{
		if (data.name == name)
		{
			data.string = new wchar_t[STRINGSIZE_MAX];
			data.pos.x = posX;
			data.pos.y = posY;

			va_list arg_ptr;

			va_start(arg_ptr, format);
			vswprintf(data.string, STRINGSIZE_MAX, format, arg_ptr);
			va_end(arg_ptr);

			
			return true;
		}
	}

	TextData data;
	data.name = name;
	data.string = new wchar_t[STRINGSIZE_MAX];
	data.pos.x = posX;
	data.pos.y = posY;

	va_list arg_ptr;

	va_start(arg_ptr, format);
	vswprintf(data.string, STRINGSIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
	m_data.push_back(data);
	return false;
	
}
// �\�����o�^(Vector2��)
bool Font::Print(wchar_t* name, DirectX::SimpleMath::Vector2 pos, wchar_t const * const format, ...)
{
	for (TextData& data : m_data)
	{
		if (data.name == name)
		{

			data.pos = pos;
			data.string = new wchar_t[STRINGSIZE_MAX];

			va_list arg_ptr;

			va_start(arg_ptr, format);
			vswprintf(data.string, STRINGSIZE_MAX, format, arg_ptr);
			va_end(arg_ptr);

			m_data.push_back(data);
			return true;
		}
	}
	TextData data;
	data.name = name;
	data.pos = pos;
	data.string = new wchar_t[STRINGSIZE_MAX];

	va_list arg_ptr;

	va_start(arg_ptr, format);
	vswprintf(data.string, STRINGSIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);

	m_data.push_back(data);

	return true;
}