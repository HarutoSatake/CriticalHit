// ゲームオブジェクトの基底クラス


#pragma once

#include <SimpleMath.h>
#include <string>
#include "GameContext.h"
#include "Projection.h"
#include "DebugMode.h"

class GameObject
{
private:
	bool m_isValid;


protected:
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;
	std::string					 m_tag;
	bool						 m_debugMode;

public:
	GameObject(const std::string& tag = "GameObject");
public:
	virtual ~GameObject() = default;


public:
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;

	virtual void OnCollision(GameObject* object) = 0;
public:
	void Invalidate();
	bool IsValid() const;
	bool IsInvalid() const;

	const std::string& GetTag() const;
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetScale() const;

	void SetPosition(DirectX::SimpleMath::Vector3& position);
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	void SetDebugMode(const bool& value);


public:
	static void Destroy(GameObject* object);
};

inline bool GameObject::IsValid() const
{
	return m_isValid;
}



inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}



inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}



inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}



inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}

inline const std::string & GameObject::GetTag() const
{
	return m_tag;
}



inline void GameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}



inline void GameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}



inline void GameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}



inline void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}

inline void GameObject::SetDebugMode(const bool& value)
{
	m_debugMode = value;
}