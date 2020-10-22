#include "..\..\pch.h"
#include "SkyDoom.h"
#include "..\..\GameContext.h"
#include "..\..\DeviceResources.h"
#include "..\..\View.h"
#include "..\..\UI\Font.h"

#include <Effects.h>
#include <CommonStates.h>


SkyDoom::SkyDoom()
	: GameObject("SkyDoom")
	, m_angle(0.0f)
{
	m_position = DirectX::SimpleMath::Vector3(0.0f,-5.0f,0.0f);
	
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	
	// モデル描画
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(deviceResources->GetD3DDevice());

	// ジオメトリ生成
	m_pTestGeo = DirectX::GeometricPrimitive::CreateSphere(deviceResources->GetD3DDeviceContext(),50.0f);
	factory->SetDirectory(L"Resources/Models");

	m_pModel = DirectX::Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/SkyDoom.cmo",
		*factory);

	delete factory;
}


SkyDoom::~SkyDoom()
{
}

void SkyDoom::Update(float elapsedTime)
{
	// 不使用
	(void)elapsedTime;
	m_angle += 0.005f;
}

void SkyDoom::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(0.1f, 0.1f, 0.1f);
	world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	
	m_pModel->UpdateEffects([&](DirectX::IEffect* effect)
	{
		DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定
			basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		}
	});

	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	Projection* proj = GameContext<Projection>().Get();
	View* view = GameContext<View>().Get();
	DirectX::CommonStates* states = GameContext<DirectX::CommonStates>().Get();

	m_pModel->Draw(deviceContext, *states, world, view->GetMatrix(), proj->GetMatrix());


}

void SkyDoom::OnCollision(GameObject * object)
{
	// 不使用
	(void)object;
}
