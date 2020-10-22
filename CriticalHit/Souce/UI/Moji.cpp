#include "..\pch.h"
#include "Moji.h"
#include <SpriteBatch.h>
#include "..\GameContext.h"


Moji::Moji()
	: m_texture(nullptr), m_x(0), m_y(0), m_color(DirectX::Colors::White)
{
}

void Moji::Initialize(ID3D11ShaderResourceView * texture, int x, int y, const char* str, DirectX::FXMVECTOR color)
{
	m_texture = texture;
	m_x = x;
	m_y = y;
	SetStr(str);
	m_color = color;
}

void Moji::Draw()
{
	int x = m_x;
	int y = m_y;

	if (!m_texture) return;

	for (size_t i = 0; i < m_str.size(); i++)
	{
		if (m_str[i] >= '0' && m_str[i] <= 'Z')
		{
			// 0の文字コードは48　そこから1ずつ増えていく
			// そこからは列と行
			int val = m_str[i] - '0';
			int xx = val % 16;
			int yy = val / 16;
			RECT srcRect = { xx * SIZE, yy * SIZE, (xx + 1) * SIZE, (yy + 1) * SIZE };
			GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture, DirectX::SimpleMath::Vector2((float)x, (float)y), &srcRect, m_color);
		}
		x += SIZE;
	}
}

void Moji::SetStr(const char * str)
{
	m_str = std::string(str);
}

void Moji::SetPos(int x, int y)
{
	m_x = x;
	m_y = y;
}
