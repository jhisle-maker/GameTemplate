#include "pch.h"
#include "ServicesContext.h"

namespace GT
{
	ServicesContext::ServicesContext
	(
		IFileLoaderService& i_oFileLoaderService,
		IShaderLoaderService& i_oShaderLoaderService,
		ITextureLoaderService& i_oTextureLoaderService
	)
		: m_oFileLoaderService(i_oFileLoaderService)
		, m_oShaderLoaderService(i_oShaderLoaderService)
		, m_oTextureLoaderService(i_oTextureLoaderService)
	{
		//Nothing to do here
	}

	ServicesContext::~ServicesContext()
	{
		//Nothing to do here
	}
}