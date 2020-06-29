#include "pch.h"
#pragma warning(disable: 4100)
#include "TitleScene.h"
#include "Font.h"
#include "Projection.h"
#include "DeviceResources.h"
#include <WICTextureLoader.h>
#include <Keyboard.h>

#include "Adx2Le.h"
#include "..\..\Resources\Sound\Soundcue.h"

TitleScene::TitleScene()
	: m_wait(0.0f)
	, m_nextscene(false)
	, m_begin(true)
{

}


TitleScene::~TitleScene()
{
	
}

void TitleScene::Initialize()
{
	GameContext<Adx2Le>::Get()->SetVolume(0.5f);
	GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_TITLE);
	auto context = GameContext<DX::DeviceResources>::Get()->GetD3DDeviceContext();
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	DirectX::CreateWICTextureFromFile(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(), L"Resources\\Textures\\Title.png", nullptr, m_texture.GetAddressOf());
	m_pos = DirectX::SimpleMath::Vector2(0.0f,0.0f);
	GameContext<EffectManager>::Get()->TimerReset();
}

void TitleScene::Update(float elapedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* key = GameContext<DirectX::Keyboard::KeyboardStateTracker>::Get();
	if (m_begin)
	{
		if (m_wait > 1.0f)
		{
			m_begin = false;
			m_wait = 0.0f;
		}
		m_wait += elapedTime;
	}
	else
	{
		if (key->IsKeyPressed(DirectX::Keyboard::Space) && m_nextscene != true)
		{
			m_nextscene = true;
			GameContext<EffectManager>::Get()->TimerReset();
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_ENTER);
		}
		if (m_nextscene)
		{
			if (m_wait > 1.0f)
			{
				GameContext<GameSceneManager>::Get()->RequestScene("Play");
			}
			m_wait += elapedTime;
		}
	}
	// エフェクトマネージャー
	m_camera = DirectX::SimpleMath::Vector3(5.0f * static_cast<float>(sin(0)), 0.0f, 5.0f * static_cast<float>(cos(0)));
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camera,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::UnitY);
	Projection* proj = GameContext<Projection>::Get();
	GameContext<EffectManager>::Get()->SetRenderState(m_camera, m_view,proj->GetMatrix());
}

void TitleScene::Render()
{
	//Font::GetInstance()->Print(L"TitleUI", 250, 120, L"ここはタイトルシーンです。");
	/*Font::GetInstance()->Print(L"Push", 240, 300, L"-- スペースを押してください --");*/
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_pos);
	m_spriteBatch->End();

	if (m_begin)
	{
		GameContext<EffectManager>::Get()->Render(EffectManager::FADE_OUT);
	}
	
	if (m_nextscene)
	{
		GameContext<EffectManager>::Get()->Render(EffectManager::FADE_IN);
	}
}

void TitleScene::Finalize()
{
	Font::GetInstance()->reset();
	GameContext<Adx2Le>::Get()->Stop();
}
