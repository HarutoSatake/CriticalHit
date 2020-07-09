// ゲームコンテキスト(登録された一つのクラスを読み込むことのできるクラス)
// 佐竹晴登

#pragma once

// ヘッダインクルード
#include <cassert>
#include <memory>

template<typename Context>
// ゲームコンテキストクラス
class GameContext final
{
private:
	// 登録されたコンテキスト
	static Context* s_context;

public:
	// コンテキストを登録する
	static void Register(const std::unique_ptr<Context>& context)
	{
		s_context = context.get();
	}

	// コンテキストを取得する
	static Context* Get()
	{
		assert(s_context && "不正なコンテキストです。");

			return s_context;
	}
};

template<typename Context>
Context* GameContext<Context>::s_context = nullptr;