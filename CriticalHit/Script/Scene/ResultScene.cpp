#include "pch.h"
#pragma warning(disable: 4100)
#include <Keyboard.h>
#include <SpriteBatch.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ResultScene.h"
#include "Font.h"
#include "DeviceResources.h"
#include "ScoreManager.h"
#include "Projection.h"
#include "picojson.h"
#include <WICTextureLoader.h>
#include "EffectManager.h"

#include "Adx2Le.h"
#include "..\..\Resources\Sound\Soundcue.h"

ResultScene::ResultScene()
	: m_begin(true)
	, m_nextscene(false)
	, m_wait(0.0f)
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_RESULT);
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	// テクスチャの読み込み（表背景）
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\Result_FRONT.png",
		nullptr, m_BG_FRONTTexture.GetAddressOf());
	// テクスチャの読み込み（表背景）
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\Result_BACK.png",
		nullptr, m_BG_BACKTexture.GetAddressOf());
	// テクスチャの読み込み（文字）
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\Font.png",
		nullptr, m_mojiTexture.GetAddressOf());
	m_score = ScoreManager::GetInstance()->GetScore();
	std::string score_str = std::to_string(m_score);

	int highScore = 0;
	// テクスチャ生成
	// 文字クラス生成
	m_ScoreMoji.Initialize(m_mojiTexture.Get(), 400, 200, score_str.data(), DirectX::Colors::Black);
	// JSONデータの読み込み
	std::ifstream ifs("Resources\\Data\\score.json");
	if (ifs.fail())
	{
		assert("ファイルが見つかりません");
	}
	// value型(値）
	picojson::value value;
	ifs >> value;
	// エネミーのマップデータ取得
	picojson::object& obj = value.get<picojson::object>();
	highScore = static_cast<int>(obj["High Score"].get<double>());
	ifs.close();
	/*if (m_score > highScore)
	{
		highScore = m_score;
		Font::GetInstance()->Print(L"HighScore", 240, 170, L"NewRecord!!");
	}*/

	picojson::object root;
	root["High Score"] = picojson::value(static_cast<double>(highScore));
	root["Score"] = picojson::value(static_cast<double>(m_score));

	picojson::value json = picojson::value(root);

	std::ofstream ofs("Resources\\Data\\score.json");
	ofs << json;

	GameContext<EffectManager>::Get()->TimerReset();
}

void ResultScene::Update(float elapedTime)
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
				GameContext<GameSceneManager>::Get()->RequestScene("Title");
			}
			m_wait += elapedTime;
		}
	}
	
	// エフェクトマネージャー
	m_camera = DirectX::SimpleMath::Vector3(5 * sin(0), 0, 5 * cos(0));
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camera,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::UnitY);
	Projection* proj = GameContext<Projection>::Get();
	GameContext<EffectManager>::Get()->SetRenderState(m_camera, m_view, proj->GetMatrix());
}

void ResultScene::Render()
{
	
	// 背景画像（裏）
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_BG_BACKTexture.Get(), DirectX::SimpleMath::Vector2::Zero);
	// 背景画像（表）
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_BG_FRONTTexture.Get(), DirectX::SimpleMath::Vector2::Zero);
	m_ScoreMoji.Draw();
	GameContext<DirectX::SpriteBatch>::Get()->End();
	if (m_begin)
	{
		GameContext<EffectManager>::Get()->Render(EffectManager::FADE_OUT);
	}
	if (m_nextscene)
	{
		GameContext<EffectManager>::Get()->Render(EffectManager::FADE_IN);
	}
	GameContext<DirectX::SpriteBatch>::Get()->Begin();
}

void ResultScene::Finalize()
{
	GameContext<Adx2Le>::Get()->Stop();
	Font::GetInstance()->reset();
	ScoreManager::GetInstance()->ScoreReset();
}
