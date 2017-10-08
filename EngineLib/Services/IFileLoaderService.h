#pragma once
#include<vector>
#include<string>
#include<inttypes.h>

namespace GT
{
	class IFileLoaderService
	{
	public:
		IFileLoaderService() {}
		virtual ~IFileLoaderService() {}

	public:
		virtual void Load(const std::string& i_ofilePath, std::vector<uint8_t>& o_oFileData) const = 0;
	};
}
