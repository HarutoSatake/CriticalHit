// ゲームシーンクラスのインターフェース
// 佐竹晴登

#pragma once

// ヘッダインクルード
#include "StepTimer.h"
#include "GameContext.h"
#include "Manager\GameSceneManager.h"

// ゲームシーンクラス
class GameScene
{
public:
	// コンストラクタ
	GameScene() = default;

public:
	// デストラクタ
	virtual ~GameScene() = default;

public:
	// 初期化処理
	virtual void Initialize() = 0;
	// 更新処理
	virtual void Update(float elapsedTime) = 0;
	// 描画処理
	virtual void Render() = 0;
	// 終了処理
	virtual void Finalize() = 0;
};