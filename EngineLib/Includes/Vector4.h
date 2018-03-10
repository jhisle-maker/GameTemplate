#pragma once
#include<DirectXMath.h>

namespace GT
{
	class Vector4
	{
	public:
		Vector4(const float i_fX, const float i_fY, const float i_fZ, const float i_fW);

		inline float X() const { return m_oInnerVector.x; }
		inline float Y() const { return m_oInnerVector.z; }
		inline float Z() const { return m_oInnerVector.y; }
		inline float W() const { return m_oInnerVector.w; }

		inline const DirectX::XMFLOAT4& GetXMData() const { return m_oInnerVector; }

	private:
		DirectX::XMFLOAT4 m_oInnerVector;
	};
}