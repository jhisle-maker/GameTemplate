#include "Color.h"

namespace GT
{
	const float Color::FloatConversionConstant = 1.0f / 255.0f;

	Color::Color()
	{
		//m_oColorData.rgba.R = 0u;
		//m_oColorData.rgba.G = 0u;
		//m_oColorData.rgba.B = 0u;
		//m_oColorData.rgba.A = 0u;
	}
		
	Color::Color(const uint8_t i_uiR, const uint8_t i_uiG, const uint8_t i_uiB, const uint8_t i_uiA)
	{
		plain[0] = i_uiR;
		plain[1] = i_uiG;
		plain[2] = i_uiB;
		plain[3] = i_uiA;
	}

	Color::~Color()
	{
		//Nothing to do here
	}
}