
#pragma once

#include <SimpleMath.h>

class View final
{
private:
	DirectX::SimpleMath::Matrix m_matrix;

public:
	View() = default;
public:
	~View() = default;

public:
	const DirectX::SimpleMath::Matrix& GetMatrix() const;
	const void CreateLookAt(const DirectX::SimpleMath::Vector3& eye, 
							const DirectX::SimpleMath::Vector3& target,
							const DirectX::SimpleMath::Vector3 up);
};

inline const DirectX::SimpleMath::Matrix& View::GetMatrix() const
{
	return m_matrix;
}

inline const void View::CreateLookAt(const DirectX::SimpleMath::Vector3 & eye, const DirectX::SimpleMath::Vector3 & target, const DirectX::SimpleMath::Vector3 up)
{
	m_matrix = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);
	return void();
}
