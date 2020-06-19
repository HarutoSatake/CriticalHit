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
	// 範囲for文
	for (GameObjectPtr& object : m_objects)
	{
		object->Update(elapsedTime);
	}

}



void GameObjectManager::AcceptObjects()
{
	// 要素の移動
	m_objects.splice(m_objects.end(), m_objectQueue);
}



void GameObjectManager::DestroyObjects()
{
	// 削除のフラグが立ったオブジェクトを全て破棄する
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
	// 全てのオブジェクトを問答無用で破棄する(シーン遷移時用処理）
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
// タグの検索
// 戻り値をboolで引数にVectorのポインタ持ってこれば使いやすくなると思います
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