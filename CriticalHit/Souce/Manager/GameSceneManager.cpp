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

	// ���N�G�X�g����Ă����ꍇ�̓V�[���J�ڂ���B
	if (!m_nextSceneName.empty())
	{
		ChangeScene();
	}

	assert(m_scenes.size() > 0 && "�A�N�e�B�u�V�[����������܂���B");
	m_scenes.back()->Update(elapsedTime);
}

void GameSceneManager::Render()
{
	assert(m_scenes.size() > 0 && "�A�N�e�B�u�V�[����������܂���");

	for (const ScenePtr& state : m_scenes)
	{
		state->Render();
	}
}

void GameSceneManager::RequestScene(const std::string& sceneName)
{
	assert(m_sceneFactories.count(sceneName) == 1 && "����Ȗ��O�̃V�[���͒m��Ȃ��ł��B");

	// �v�f�����擾(int�^)
	m_popCount = m_scenes.size();
	m_nextSceneName = sceneName;
}

void GameSceneManager::PushScene(const std::string& stateName)
{
	// ���̃V�[�������߂�
	m_nextSceneName = stateName;
}

void GameSceneManager::PopScene(int count)
{
	assert(count > 0 && "���̃J�E���g�͖����ł��B");

	if (!m_nextSceneName.empty())
	{
		m_nextSceneName.clear();
		count--;
	}

	// PopCount�킩��Ȃ�
	m_popCount = Clamp<int>(m_popCount + count, 0, m_scenes.size() - 1);
}

void GameSceneManager::ChangeScene()
{
	// ���X�g�v�b�V���o�b�N���Ă��疖���i�ǉ�������j�̏������������s���B
	m_scenes.push_back(m_sceneFactories[m_nextSceneName]());
	m_scenes.back()->Initialize();

	// ���̃V�[������ɂ���
	m_nextSceneName.clear();
}