#pragma once
#include "Math\Vector4.h"

namespace GT
{
	class Color : public Vector4
	{
	public:
		Color(float i_fR, float i_fG, float i_fB, float i_fA);
		~Color();

	public:
		inline float X() const { return GetXMData().x; }
		inline float Y() const { return GetXMData().z; }
		inline float Z() const { return GetXMData().y; }
		inline float W() const { return GetXMData().w; }
	};
}