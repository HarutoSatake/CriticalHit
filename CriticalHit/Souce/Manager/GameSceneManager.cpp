#include "..\pch.h"
#include "GameSceneManager.h"

#include <cassert>


#include "..\GameScene.h"
#include "..\Utilities.h"

GameSceneManager::GameSceneManager()
	: m_sceneFactories()
	, m_scenes()
	, m_popCount(0)
	, m_nextSceneName()
{

}


GameSceneManager::~GameSceneManager()
{
}

void GameSceneManager::SetStartScene(const std::string& sceneName)
{
	RequestScene(sceneName);
}

void GameSceneManager::Update(float elapsedTime)
{

	if (m_popCount > 0)
	{
		for (int i = 0; i < m_popCount; i++)
		{
			m_scenes.back()->Finalize();
			m_scenes.pop_back();
		}
		m_popCount = 0;
	}

	// リクエストされていた場合はシーン遷移する。
	if (!m_nextSceneName.empty())
	{
		ChangeScene();
	}

	assert(m_scenes.size() > 0 && "アクティブシーンが見つかりません。");
	m_scenes.back()->Update(elapsedTime);
}

void GameSceneManager::Render()
{
	assert(m_scenes.size() > 0 && "アクティブシーンが見つかりません");

	for (const ScenePtr& state : m_scenes)
	{
		state->Render();
	}
}

void GameSceneManager::RequestScene(const std::string& sceneName)
{
	assert(m_sceneFactories.count(sceneName) == 1 && "そんな名前のシーンは知らないです。");

	// 要素数を取得(int型)
	m_popCount = m_scenes.size();
	m_nextSceneName = sceneName;
}

void GameSceneManager::PushScene(const std::string& stateName)
{
	// 次のシーンを決める
	m_nextSceneName = stateName;
}

void GameSceneManager::PopScene(int count)
{
	assert(count > 0 && "そのカウントは無効です。");

	if (!m_nextSceneName.empty())
	{
		m_nextSceneName.clear();
		count--;
	}

	// PopCountわかんない
	m_popCount = Clamp<int>(m_popCount + count, 0, m_scenes.size() - 1);
}

void GameSceneManager::ChangeScene()
{
	// リストプッシュバックしてから末尾（追加したやつ）の初期化処理を行う。
	m_scenes.push_back(m_sceneFactories[m_nextSceneName]());
	m_scenes.back()->Initialize();

	// 次のシーンを空にする
	m_nextSceneName.clear();
}