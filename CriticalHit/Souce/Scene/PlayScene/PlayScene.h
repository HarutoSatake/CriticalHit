// プレイシーンのソース
#pragma once

#include "..\..\GameScene.h"
#include <Keyboard.h>

#include "..\..\Manager\GameObjectManager.h"
#include "..\..\GameObject\DebugCamera.h"
#include "..\..\GameObject\TargetCamera.h"
#include "..\..\GameObject\FixedCamera.h"
#include "..\..\GameObject\GridFloor.h"
#include "..\..\UI\Moji.h"

class PlayScene :
	public GameScene
{
public:
	enum State
	{
		STATE_DEMO,		// デモ中
		STATE_PLAY,		// プレイ中(操作可能)
		STATE_CLEAR,	// クリア
		STATE_DEAD,		// 死亡

		SUM_STATE
	};

public:
	PlayScene();
	~PlayScene();
	
	// 公開処理

	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float elapedTime) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;
	// 更新処理(デモ中) 
	void StateDemo(float elapedTime);
	// 更新処理(プレイ中)
	void StatePlay(float elapedTime);
	// 更新処理(クリア)
	void StateClear(float elasedTime);
	// 更新処理
	void StateDead(float elasedTime);

private:
	// デバッグカメラ
	std::unique_ptr<DebugCamera>			m_pDebugCamera;
	// ターゲットカメラ
	std::unique_ptr<TargetCamera>			m_pTargetCamera;
	// 固定カメラ
	std::unique_ptr<FixedCamera>			m_pFixedCamera;
	// グリッドフロア
	std::unique_ptr<GridFloor>				m_pGridFloor;
	// キーボードトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_pKeyboardTracker;
	// フェードアウトの時間
	float									m_fadeTime;
	// カウント
	int										m_count;
	// デバッグカメラとの切り替え
	bool									m_debugCameraMode;
	// デバッグモード
	bool									m_debugMode;
	// タイム進行の切り替え
	bool									m_debugTimeMode;
	// ステート管理
	State									m_state;
	// オブジェクトマネージャー
	std::unique_ptr<GameObjectManager>		m_pGameObjectManager;
	// タイム用の文字
	Moji									m_timeMoji;
	// 文字のテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureMoji;
	float									m_wait;

};

