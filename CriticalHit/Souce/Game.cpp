//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "GameContext.h"

#include "Scene\TitleScene\TitleScene.h"
#include "Scene\PlayScene\PlayScene.h"
#include "Scene\ResultScene\ResultScene.h"

#include "Manager\ScoreManager.h"
extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	GameContext<DX::DeviceResources>::Register(m_deviceResources);

	m_pEffectManager = nullptr;
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{

	// マウスの作成
	m_pMouse = std::make_unique<Mouse>();
	m_pMouse->SetWindow(window);
	// キーボードの作成
	m_pKeyBoard = std::make_unique<Keyboard>();

	// キーボードトラッカーの作成
	m_pKeyStateTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	GameContext<Keyboard::KeyboardStateTracker>::Register(m_pKeyStateTracker);

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

	
	

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();



    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	// フォント生成
	Font::GetInstance()->Create(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());
	// シーンマネージャー生成
	m_pGameSceneManager = std::make_unique<GameSceneManager>();
	// ゲームシーンの追加
	m_pGameSceneManager->registerScene<TitleScene>("Title");
	m_pGameSceneManager->registerScene<PlayScene>("Play");
	m_pGameSceneManager->registerScene<ResultScene>("Result");

	// どのシーンから始めるか
	m_pGameSceneManager->SetStartScene("Title");

	// シーンマネージャーをコンテキストに追加(どこでも呼び出せるように）
	// <>を先に置く意味がテンプレート指定ってことに気付きました
	GameContext<GameSceneManager>::Register(m_pGameSceneManager);


	// コリジョンマネージャー生成
	m_pCollisionManager = std::make_unique<CollisionManager>();

	GameContext<CollisionManager>::Register(m_pCollisionManager);

	// 画面設定
	m_camera = DirectX::SimpleMath::Vector3(0, 0, -5);
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camera,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::UnitY);

	m_pEffectManager = std::make_unique<EffectManager>();
	m_pEffectManager->Create(m_deviceResources.get(), L"Resources\\Textures\\Title.png", 1);
	m_pEffectManager->InitializeCorn(5, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3(0, 1, 0));
	m_pEffectManager->SetRenderState(m_camera, m_view, m_projection->GetMatrix());
	GameContext<EffectManager>::Register(m_pEffectManager);
	// スコアマネージャー生成
	ScoreManager::GetInstance();

	m_pAdx2le = std::make_unique<Adx2Le>();

	m_pAdx2le->Initialize(L"Resources\\Sound\\Sound.acf");

	m_pAdx2le->LoadAcbFile(L"Resources\\Sound\\Soundcue.acb");

	
	GameContext<Adx2Le>::Register(m_pAdx2le);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
	// ゲームシーンマネージャー(ゲームシーン管理)の更新
	m_pGameSceneManager->Update(elapsedTime);
	// コリジョンマネージャー(当たり判定管理)の更新
	m_pCollisionManager->DetectCollision();
	// 音声管理クラスの更新
	m_pAdx2le->Update();
	// エフェクトマネージャー(エフェクト管理)の更新
	GameContext<EffectManager>::Get()->Update(timer);
	// キーボードトラッカー(DirectXTKのキーボード入力管理)の更新
	m_pKeyStateTracker->Update(m_pKeyBoard->GetState());
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	// スプライトバッチ描画処理開始
	m_pSprite->Begin(DirectX::SpriteSortMode_Deferred, m_pStates->NonPremultiplied());
	// シーンの描画処理
	m_pGameSceneManager->Render();
	// フォント表示
	Font::GetInstance()->Render();
	// スプライトバッチ描画処理終了
	m_pSprite->End();

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();
    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// スプライトバッチの生成
	m_pSprite = std::make_unique<SpriteBatch>(context);
	GameContext<SpriteBatch>::Register(m_pSprite);
	// コモンステートの生成
	m_pStates = std::make_unique<CommonStates>(device);
	GameContext<CommonStates>::Register(m_pStates);

	// ポリゴン
	m_pBasicEffect = std::make_unique<BasicEffect>(device);
	// ライト有効
	m_pBasicEffect->SetLightingEnabled(true);
	// 環境光の色を設定
	m_pBasicEffect->SetAmbientLightColor(SimpleMath::Vector3(0.2f, 0.2f, 0.2f));
	// 拡散反射光の素材色を設定
	m_pBasicEffect->SetDiffuseColor(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	// ライト0番を有効
	m_pBasicEffect->SetLightEnabled(0, true);
	// ライト0番の色設定
	m_pBasicEffect->SetLightDiffuseColor(0, SimpleMath::Vector3(0.2f, 0.8f, 0.2f));
	// ライト0番の向きを設定
	m_pBasicEffect->SetLightDirection(0, SimpleMath::Vector3(-1.0f, -0.5f, -2.0f));
	
	void const * shaderByteCode;
	size_t byteCodeLength;

	// シェーダー取得
	m_pBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// 入力レイアウトの作成
	device->CreateInputLayout(VertexPositionNormal::InputElements,
		VertexPositionNormal::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_pInputLayout.GetAddressOf());

	GameContext<BasicEffect>::Register(m_pBasicEffect);

}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// ウィンドウサイズからアスペクト比を算出する。
	RECT size = m_deviceResources->GetOutputSize();
	/*float aspectRatio = float(size.right) / float(size.bottom);*/
	RECT outputSize = m_deviceResources->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);
	//// 画角を設定
	//float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = std::make_unique<Projection>();
	m_projection->SetPerspectiveFieldOfview(
		XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight),
			0.01f,
			100.0f);

	// コンテキストにプロジェクション座標追加
	GameContext<Projection>::Register(m_projection);

}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
