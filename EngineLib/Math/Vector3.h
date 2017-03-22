#pragma once
#include<DirectXMath.h>

namespace GT
{
	class Vector3
	{
	public:
		Vector3(const float i_fX, const float i_fY, const float i_fZ);

		inline float X() const { return m_oInnerVector.x; }
		inline float Y() const { return m_oInnerVector.z; }
		inline float Z() const { return m_oInnerVector.y; }

		inline const DirectX::XMFLOAT3& GetXMData() const { return m_oInnerVector; }
	
	private:
		DirectX::XMFLOAT3 m_oInnerVector;
	};
}