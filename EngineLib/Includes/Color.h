#pragma once
#include <inttypes.h>
#include <vector>

namespace GT
{
	class Color
	{
	public:
		Color();
		Color(const uint8_t i_uiR, const uint8_t i_uiG, const uint8_t i_uiB, const uint8_t i_uiA);
		~Color();

	public:
		inline uint8_t R() const { return plain[0]; }
		inline uint8_t G() const { return plain[1]; }
		inline uint8_t B() const { return plain[2]; }
		inline uint8_t A() const { return plain[3]; }

		inline std::vector<float> ToFloat4()
		{
			return
			{
				plain[0] * FloatConversionConstant,
				plain[1] * FloatConversionConstant,
				plain[2] * FloatConversionConstant,
				plain[3] * FloatConversionConstant
			};
		}

	
	private:
		static const float FloatConversionConstant;

		uint8_t plain[4];
	};
}