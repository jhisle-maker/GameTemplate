#pragma once

#include "IServicesContext.h"	

namespace GT
{
	class ServicesContext : public IServicesContext
	{
	public:
		ServicesContext
		(
			IFileLoaderService& i_oFileLoaderService,
			IShaderLoaderService& i_oShaderLoaderService,
			ITextureLoaderService& i_oTextureLoaderService
		);

		~ServicesContext();

	public:
		inline IFileLoaderService& GetFileLoaderService() const { return m_oFileLoaderService; };
		inline IShaderLoaderService& GetShaderLoaderService() const { return m_oShaderLoaderService; }
		inline ITextureLoaderService& GetTextureLoaderService() const { return m_oTextureLoaderService; }

	private:
		IFileLoaderService& m_oFileLoaderService;
		IShaderLoaderService& m_oShaderLoaderService;
		ITextureLoaderService& m_oTextureLoaderService;
	};
}
