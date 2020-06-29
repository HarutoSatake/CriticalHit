#pragma once
#include "GameObject.h"
#include <Model.h>
#include <GeometricPrimitive.h>

class Ground :
	public GameObject
{
public:
	// ��]���x
	static constexpr float ROTATION_SPEED = 0.01f;
public:
	Ground();
	~Ground();
private:
	// ���f��
	std::unique_ptr<DirectX::Model>	 m_pModel;
	// �W�I���g��
	std::unique_ptr<DirectX::GeometricPrimitive> m_pTestGeo;
	// ��]
	float							 m_angle;
public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
};

