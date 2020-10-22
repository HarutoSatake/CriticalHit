#pragma once
#include "..\..\GameObject\GameObject.h"
#include <GeometricPrimitive.h>
#include "..\..\Collider\BoxCollider.h"

class PseudoObject :
	public GameObject
{
public:


public:
	PseudoObject(const DirectX::SimpleMath::Vector3& startPos,DirectX::SimpleMath::Vector3& endPos,const float& difference = 0.0f);
	~PseudoObject() = default;
public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_GeometricPrimitive;
	std::unique_ptr<DirectX::GeometricPrimitive> m_ColliderModel;
	std::unique_ptr<BoxCollider> m_boxCollider;
	DirectX::SimpleMath::Vector3 m_velocity;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Vector3 m_startPos;
	DirectX::SimpleMath::Vector3 m_endPos;
	DirectX::SimpleMath::Vector4 m_color;
};

