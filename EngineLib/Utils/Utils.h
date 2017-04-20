#pragma once
#include <memory>
#include <fstream>
#include <vector>
#include <cstdint>

namespace GT
{
	typedef unsigned char byte;

	class Utils
	{
	public:
		static inline void ReadFileBytes(const std::string& i_oFileName, std::vector<uint8_t>& o_oBuffer)
		{
			o_oBuffer.clear();
			std::ifstream fileStream = std::ifstream();

			fileStream.open(i_oFileName.c_str(), std::ios::in | std::ios::binary);
			if (fileStream.is_open())
			{
				o_oBuffer.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
			}
			fileStream.close();
		}
	};
}

