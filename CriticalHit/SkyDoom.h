#pragma once
#include <Model.h>

#include "GameObject.h"
#include <GeometricPrimitive.h>

class SkyDoom :
	public GameObject
{
public:
	// ��]���x
	static constexpr float ROTATION_SPEED = 0.01f;
public:
	SkyDoom();
	~SkyDoom();
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

