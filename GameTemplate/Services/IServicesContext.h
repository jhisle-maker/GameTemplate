#pragma once

#include "Services\IFileLoaderService.h"
#include "Services\IShaderLoaderService.h"
#include "Services\ITextureLoaderService.h"

namespace GT
{
	class IServicesContext
	{
	public:
		IServicesContext() {};
		virtual ~IServicesContext() {};

		virtual IFileLoaderService& GetFileLoaderService() const = 0;
		virtual IShaderLoaderService& GetShaderLoaderService() const = 0;
		virtual ITextureLoaderService& GetTextureLoaderService() const = 0;
	};
}