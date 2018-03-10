#pragma once
#include<memory>
#include<string>

namespace GT { class IFile; }

namespace GT
{
	class IFileLoaderService
	{
	public:
		IFileLoaderService() {}
		virtual ~IFileLoaderService() {}

	public:
		virtual std::unique_ptr<IFile> Load(const std::string& i_ofilePath) const = 0;
	};
}
