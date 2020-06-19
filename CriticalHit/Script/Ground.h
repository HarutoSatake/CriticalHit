#pragma once
#include "GameObject.h"
#include <Model.h>
#include <GeometricPrimitive.h>

class Ground :
	public GameObject
{
public:
	// 回転速度
	static constexpr float ROTATION_SPEED = 0.01f;
public:
	Ground();
	~Ground();
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

