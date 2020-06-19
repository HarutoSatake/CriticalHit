#pragma once
#include <Model.h>

#include "GameObject.h"
#include <GeometricPrimitive.h>

class SkyDoom :
	public GameObject
{
public:
	// 回転速度
	static constexpr float ROTATION_SPEED = 0.01f;
public:
	SkyDoom();
	~SkyDoom();
private:
	// モデル
	std::unique_ptr<DirectX::Model>	 m_pModel;
	// ジオメトリ
	std::unique_ptr<DirectX::GeometricPrimitive> m_pTestGeo;
	// 回転
	float							 m_angle;
public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;

};

