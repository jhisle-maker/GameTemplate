#pragma once
#include<vector>
#include<string>
#include<inttypes.h>

namespace GT
{
	class IFileLoader
	{
	public:
		IFileLoader() {}
		virtual ~IFileLoader() {}

	public:
		virtual void Load(const std::string& i_ofilePath, std::vector<uint8_t>& o_oFileData) const = 0;
	};
}
