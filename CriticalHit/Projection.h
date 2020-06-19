#pragma once

#include <SimpleMath.h>

class Projection final
{
private:
	DirectX::SimpleMath::Matrix m_matrix;

public:
	Projection() = default;
public:
	~Projection() = default;

public:
	const DirectX::SimpleMath::Matrix& GetMatrix() const;

	void SetPerspectiveFieldOfview(float fov, float aspecRatio, float nearPlane, float farPlane);

};

inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}
inline void Projection::SetPerspectiveFieldOfview(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_matrix
		= DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
}