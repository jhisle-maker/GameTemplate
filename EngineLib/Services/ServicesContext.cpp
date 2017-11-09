#include "ServicesContext.h"

#include "Services\IFileLoaderService.h"
#include "Services\IShaderLoaderService.h"
#include "Services\ITextureLoaderService.h"
#include "Services\IShaderManagerService.h"

namespace GT
{
	Context::Context
	(
		IGraphicDevice& i_oGraphicDevice,
		IGraphicContext& i_oGraphicContext,
		IFileLoaderService& i_oFileLoaderService,
		IShaderLoaderService& i_oShaderLoaderService,
		ITextureLoaderService& i_oTextureLoaderService,
		IShaderManagerService& i_oShaderManagerService
	)
		: m_oGraphicDevice(i_oGraphicDevice)
		, m_oGraphicContext(i_oGraphicContext)
		, m_oFileLoaderService(i_oFileLoaderService)
		, m_oShaderLoaderService(i_oShaderLoaderService)
		, m_oTextureLoaderService(i_oTextureLoaderService)
		, m_oShaderManagerService(i_oShaderManagerService)
	{
		//Nothing to do here
	}

	Context::~Context()
	{
		//Nothing to do here
	}
}