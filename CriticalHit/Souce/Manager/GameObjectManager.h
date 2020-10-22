// ゲームオブジェクトマネージャーのヘッダ
#pragma once

#include <list>
#include <memory>
#include <SimpleMath.h>
#include <vector>

class GameObject;


class GameObjectManager final
{
	using GameObjectPtr = std::unique_ptr<GameObject>;
	using GameObjectList = std::list<GameObjectPtr>;

private:
	GameObjectList m_objects;
	GameObjectList m_objectQueue;
	GameObjectList m_result;
	bool		   m_debugMode;

public:
	GameObjectManager();

public:
	~GameObjectManager();

public:
	void Update(float elapsedTime);
	void Render();
	void Add(GameObjectPtr&& object);
	void Crear();
	void ChangeDebugMode(const bool& value);
	std::vector<GameObject*> Find(std::string tagName);

private:
	void UpdateObjects(float elapsedTime);
	void AcceptObjects();
	void DestroyObjects();

};

