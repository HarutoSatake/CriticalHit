#include "pch.h"

#include "GameObjectManager.h"

#include "GameObject.h"



GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
	, m_debugMode(false)
{
}



GameObjectManager::~GameObjectManager()
{
}



void GameObjectManager::Update(float elapsedTime)
{
	DestroyObjects();


	/*if (!m_objectQueue.empty())*/
	{
		AcceptObjects();
	}


	UpdateObjects(elapsedTime);
}



void GameObjectManager::Render()
{
	for (GameObjectPtr& object : m_objects)
	{
		object->Render();
	}
}



void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objects.push_back(std::move(object));
}



void GameObjectManager::UpdateObjects(float elapsedTime)
{
	// �͈�for��
	for (GameObjectPtr& object : m_objects)
	{
		object->Update(elapsedTime);
	}

}



void GameObjectManager::AcceptObjects()
{
	// �v�f�̈ړ�
	m_objects.splice(m_objects.end(), m_objectQueue);
}



void GameObjectManager::DestroyObjects()
{
	// �폜�̃t���O���������I�u�W�F�N�g��S�Ĕj������
	GameObjectList::iterator it = m_objects.begin();
	while (it != m_objects.end())
	{
		if ((*it)->IsInvalid())
		{
			it = m_objects.erase(it);
		}
		else
		{
			++it;
		}
	}
}
void GameObjectManager::Crear()
{
	// �S�ẴI�u�W�F�N�g��ⓚ���p�Ŕj������(�V�[���J�ڎ��p�����j
	m_objects.clear();
	m_objectQueue.clear();
	
}
void GameObjectManager::ChangeDebugMode(const bool& value)
{
	if (value)
	{
		m_debugMode = value;
		for (GameObjectPtr& object : m_objects)
		{
			object->SetDebugMode(value);
		}
	}
	else
	{
		m_debugMode = value;
		for (GameObjectPtr& object : m_objects)
		{
			object->SetDebugMode(value);
		}
	}
}
// �^�O�̌���
// �߂�l��bool�ň�����Vector�̃|�C���^�����Ă���Ύg���₷���Ȃ�Ǝv���܂�
std::vector<GameObject*> GameObjectManager::Find(std::string tagName)
{
	std::vector<GameObject*> result;
	for (GameObjectPtr& object : m_objects)
	{
		if (object->GetTag() == tagName)
		{
			result.push_back(object.get());
		}
	}
	return result;
}