#pragma once

#include "Loaders\IFileLoader.h"

namespace GT
{
	class UWPFileLoader : public IFileLoader
	{
	public:
		UWPFileLoader();
		~UWPFileLoader();

	public:
		virtual void Load(const std::string& i_ofilePath, std::vector<uint8_t>& o_oFileData) const;
	};
}