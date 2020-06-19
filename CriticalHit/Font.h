// フォントクラスのヘッダ

// 多重インクルード防止
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
// Fontクラス
class Font
{
public:
	// 文字数最大サイズ
	static constexpr size_t STRINGSIZE_MAX = 256;
private:
	Font();
public:
	~Font();
	// 生成
	void Create(ID3D11Device* device,ID3D11DeviceContext1* context);
	// 描画
	void Render();
	// リセット
	void reset();
	// 表示情報登録
	bool Print(wchar_t* name, float posX, float posY, wchar_t const* const format, ...);
	bool Print(wchar_t* name, DirectX::SimpleMath::Vector2 m_pos, wchar_t const* const format, ...);

public:
	// オブジェクトへのポインタを返す
	static Font* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// オブジェクトを生成して、ポインタを格納
			m_pInstance.reset(new Font());
		}
		// オブジェクトへのポインタを返す
		return m_pInstance.get();
	}
private:
	static std::unique_ptr<Font> m_pInstance;

// メンバ変数
private:
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;
	std::list<TextData>						m_data;
};

