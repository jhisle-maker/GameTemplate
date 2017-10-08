#pragma once

#include "Services\IFileLoaderService.h"

namespace GT
{
	class UWPFileLoaderService : public IFileLoaderService
	{
	public:
		UWPFileLoaderService();
		~UWPFileLoaderService();

	public:
		virtual void Load(const std::string& i_ofilePath, std::vector<uint8_t>& o_oFileData) const;
	};
}