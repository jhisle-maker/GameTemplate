#pragma once
#include <DirectXMath.h>

namespace GT
{
	class Vector2
	{
	public: //CTORS
		Vector2(const float i_fX, const float i_fY);

	public: //METHODS
		inline float X() const { return m_oInnerVector.x; }
		inline float Y() const { return m_oInnerVector.y; }

		inline const DirectX::XMFLOAT2& GetXMData() const { return m_oInnerVector; }

	private:
		DirectX::XMFLOAT2 m_oInnerVector;
	};
}
