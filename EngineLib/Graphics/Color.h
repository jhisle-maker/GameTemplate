#pragma once
#include <inttypes.h>

namespace GT
{
	class Color
	{
	public:
		Color();
		Color(const uint8_t i_uiR, const uint8_t i_uiG, const uint8_t i_uiB, const uint8_t i_uiA);
		~Color();

	public:
		inline uint8_t R() const { return m_oColorData.rgba.R; }
		inline uint8_t G() const { return m_oColorData.rgba.G; }
		inline uint8_t B() const { return m_oColorData.rgba.B; }
		inline uint8_t A() const { return m_oColorData.rgba.A; }

		inline const uint32_t GetInnerData() const { return m_oColorData.plain; }
		
	private:
		union ColorData
		{
			struct RGBA
			{
				uint8_t R;
				uint8_t G;
				uint8_t B;
				uint8_t A;
			};

			RGBA rgba;
			uint32_t plain;
		};

		ColorData m_oColorData;
	};
}