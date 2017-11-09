#pragma once

#include "IServicesContext.h"	

//START FORWARD DECL
namespace GT { class IGraphicDevice; }
namespace GT { class IGraphicContext; }

namespace GT { class IFileLoaderService; }
namespace GT { class IShaderLoaderService; }
namespace GT { class ITextureLoaderService; }
namespace GT { class IShaderManagerService; }
//END FORWARD DECL


namespace GT
{
	class Context : public IContext
	{
	public:
		Context
		(
			IGraphicDevice& i_oGraphicDevice,
			IGraphicContext& i_oGraphicContext,
			IFileLoaderService& i_oFileLoaderService,
			IShaderLoaderService& i_oShaderLoaderService,
			ITextureLoaderService& i_oTextureLoaderService,
			IShaderManagerService& i_oShaderManagerService
		);

		~Context();

	public:
		inline IGraphicDevice& GetGraphicDevice() const { return m_oGraphicDevice; }
		inline IGraphicContext& GetGraphicContext() const { return m_oGraphicContext; }

		inline IFileLoaderService& GetFileLoaderService() const { return m_oFileLoaderService; };
		inline IShaderLoaderService& GetShaderLoaderService() const { return m_oShaderLoaderService; }
		inline ITextureLoaderService& GetTextureLoaderService() const { return m_oTextureLoaderService; }
		inline IShaderManagerService& GetShaderManagerService() const { return m_oShaderManagerService; }

	private:
		IGraphicDevice& m_oGraphicDevice;
		IGraphicContext& m_oGraphicContext;
		IFileLoaderService& m_oFileLoaderService;
		IShaderLoaderService& m_oShaderLoaderService;
		IShaderManagerService& m_oShaderManagerService;
		ITextureLoaderService& m_oTextureLoaderService;
	};
}
