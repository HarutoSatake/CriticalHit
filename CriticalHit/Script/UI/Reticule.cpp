#include "pch.h"

#include <Mouse.h>

#include "Reticule.h"

#include "View.h"
#include "Projection.h"
#include "Utilities.h"
#include "Font.h"
#include "Utilities.h"
#include <WICTextureLoader.h>
#include <CommonStates.h>



Reticule::Reticule()
	:GameObject("Pointer")
	,m_scale(1.0f,1.0f,1.0f)
{
	m_deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = m_deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext);

	DirectX::CreateWICTextureFromFile(
		m_deviceResources->GetD3DDevice(), 
		L"\Resources\\Textures\\Retucule.png", 
		nullptr, m_texture.GetAddressOf());
}



Reticule::~Reticule()
{
}

void Reticule::Update(float elapsedTime)
{
	// マウスの取得
	DirectX::Mouse::State mouse = DirectX::Mouse::Get().GetState();
	m_mousePos = DirectX::SimpleMath::Vector2(mouse.x, mouse.y);
	Projection* proj = GameContext<Projection>().Get();
	View* view = GameContext<View>().Get();
	// ウィンドウサイズを取得
	RECT size = m_deviceResources->GetOutputSize();
	
	// マウスの二次元座標を読み取ってください
	DirectX::SimpleMath::Matrix screen2WorldMtx = CreateMatrix_Screen2World(size.right, size.bottom, view->GetMatrix(), proj->GetMatrix());
	
	DirectX::SimpleMath::Vector3 mouseStartPos(static_cast<float>(mouse.x), static_cast<float>(mouse.y), 0.0f);
	DirectX::SimpleMath::Vector3 mouseEndPos(static_cast<float>(mouse.x), static_cast<float>(mouse.y), 1.0f);
	
	// マウスの二次元座標をスクリーン座標に変換
	mouseStartPos = DirectX::SimpleMath::Vector3::Transform(mouseStartPos, screen2WorldMtx);
	mouseEndPos = DirectX::SimpleMath::Vector3::Transform(mouseEndPos, screen2WorldMtx);

	DirectX::SimpleMath::Plane plane(DirectX::SimpleMath::Vector3(0.0f,0.0f,5.0f),DirectX::SimpleMath::Vector3(0.0f,0.0f,1.0f));

	m_position = SegmentWithPlaneIntersection(mouseStartPos, mouseEndPos, plane);
	
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		Font::GetInstance()->Print(L"Reticule", 0, 210, L"マウスの座標：%f,%f,%f", m_position.x, m_position.y, m_position.z);
	}

	
}

void Reticule::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	Projection* proj = GameContext<Projection>().Get();
	View* view = GameContext<View>().Get();

	/*m_geometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(),DirectX::Colors::Blue);*/
	m_mousePos.x = m_mousePos.x - 40.0f;
	m_mousePos.y = m_mousePos.y - 40.0f;
	// ここ透明化処理
	GameContext<DirectX::SpriteBatch>::Get()->Draw(m_texture.Get(), m_mousePos);
}

void Reticule::OnCollision(GameObject * object)
{
}
