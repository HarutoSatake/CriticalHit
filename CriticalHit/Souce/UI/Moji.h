#pragma once
#include <SimpleMath.h>

class Moji
{
public:
	// 文字のサイズ
	static const int SIZE = 48;

public:
	// コンストラクタ
	Moji();

	// 初期化関数
	void Initialize(ID3D11ShaderResourceView* texture, int x, int y, const char* str, DirectX::FXMVECTOR color = DirectX::Colors::White);

	// 描画関数
	void Draw();

	// 文字列設定関数
	void SetStr(const char* str);

	// 表示位置の設定関数
	void SetPos(int x, int y);

private:
	// テクスチャハンドル
	ID3D11ShaderResourceView* m_texture;

	// 文字列
	std::string m_str;

	// 表示位置
	int m_x, m_y;

	// 文字の色
	DirectX::SimpleMath::Color m_color;
};

