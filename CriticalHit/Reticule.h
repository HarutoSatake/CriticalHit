#pragma once
#include "GameObject.h"
#include <GeometricPrimitive.h>
#include "DeviceResources.h"
#include <SpriteBatch.h>

class Reticule :
	public GameObject
{
public:
	Reticule();
	~Reticule();

public:
	void Update(float elapsedTime) override;
	void Render() override;
	void OnCollision(GameObject* object) override;
private:
	std::unique_ptr<DirectX::GeometricPrimitive>		m_geometricPrimitive;
	DirectX::SimpleMath::Vector3						m_scale;
	DX::DeviceResources*								m_deviceResources;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
	DirectX::SimpleMath::Vector2						m_mousePos;
};

