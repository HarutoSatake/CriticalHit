#include "..\..\pch.h"
#include "PseudoObject.h"
#include "..\..\DeviceResources.h"
#include "..\..\Manager\CollisionManager.h"
#include "..\..\View.h"
#include "..\..\UI\Font.h"


PseudoObject::PseudoObject(const DirectX::SimpleMath::Vector3& startPos, DirectX::SimpleMath::Vector3& endPos,const float& difference)
	: GameObject("Wall")
	, m_velocity(0.0f,0.0f,0.1f)
	, m_scale(1.0f,1.0f,1.0f)
	, m_startPos(startPos)
	, m_endPos(endPos)
{
	// ジオメトリ生成
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	m_GeometricPrimitive = DirectX::GeometricPrimitive::CreateBox(deviceContext,m_scale);
	
	// 座標情報指定
	m_startPos.y	= m_startPos.y + (m_scale.y / 2);
	m_startPos.z	= m_startPos.z + difference;
	m_position		= m_startPos;

	// スケールをランダムに設定する


	m_color = DirectX::Colors::White;
	
	// 当たり判定設定
	m_boxCollider = std::make_unique<BoxCollider>(this,m_scale);
	DirectX::SimpleMath::Vector3 size = m_boxCollider->GetSize() * 2;
	m_ColliderModel = DirectX::GeometricPrimitive::CreateBox(deviceContext, size);
}
void PseudoObject::Update(float elapsedTime)
{
	// 不使用
	(void)elapsedTime;
	
	// 等速移動
	m_position += m_velocity;

	// 終端座標を超えたら最初へ
	if (m_endPos.z <= m_position.z)
	{
		m_position.z = -15.0f;
	}
	m_boxCollider->SetOffset(m_position);
	m_boxCollider->SetOffset(m_scale);
	GameContext<CollisionManager>::Get()->add(m_boxCollider.get());

	DirectX::SimpleMath::Vector3 ColPos = m_boxCollider->GetPosition();
	DirectX::SimpleMath::Vector3 ColOffSet = m_boxCollider->GetSize();

	//Font::GetInstance()->Print(L"WallColPos", 0, 210, L"壁座標：%f,%f,%f", ColPos.x, ColPos.y, ColPos.z);
	//Font::GetInstance()->Print(L"WallColOff", 0, 240, L"壁サイズ：%f,%f,%f",ColOffSet.x, ColOffSet.y, ColOffSet.z);
	m_color = DirectX::Colors::White;
}

void PseudoObject::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	Projection* proj = GameContext<Projection>().Get();
	View* view = GameContext<View>().Get();
	m_GeometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(),m_color,nullptr,false);

	// デバッグモード処理
	if (m_debugMode)
	{
		world = DirectX::SimpleMath::Matrix::Identity;
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_boxCollider->GetPosition());
		m_ColliderModel->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Yellow, nullptr, true);
	}
	

}

void PseudoObject::OnCollision(GameObject * object)
{
	if (object->GetTag() == "Bullet")
	{
		m_color = DirectX::Colors::Red;
	}
	
}

