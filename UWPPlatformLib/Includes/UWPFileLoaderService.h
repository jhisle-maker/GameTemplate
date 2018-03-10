#pragma once

#include "IFileLoaderService.h"

//START FORWARD DECLS
namespace GT { class IFile; }
//END FORWARD DECLS

namespace GT
{
	class UWPFileLoaderService : public IFileLoaderService
	{
	public:
		UWPFileLoaderService();
		~UWPFileLoaderService();

	public:
		virtual std::unique_ptr<IFile> Load(const std::string& i_ofilePath) const;
	};
}