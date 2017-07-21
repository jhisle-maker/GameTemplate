#include "Color.h"

namespace GT
{
	Color::Color()
	{
		m_oColorData.rgba.R = 0u;
		m_oColorData.rgba.G = 0u;
		m_oColorData.rgba.B = 0u;
		m_oColorData.rgba.A = 0u;
	}
		
	Color::Color(const uint8_t i_uiR, const uint8_t i_uiG, const uint8_t i_uiB, const uint8_t i_uiA)
	{
		m_oColorData.rgba.R = i_uiR;
		m_oColorData.rgba.G = i_uiG;
		m_oColorData.rgba.B = i_uiB;
		m_oColorData.rgba.A = i_uiA;
	}

	Color::~Color()
	{
		//Nothing to do here
	}
}