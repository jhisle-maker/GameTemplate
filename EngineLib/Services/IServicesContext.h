#pragma once

//START FORWARD DECL
namespace GT { class IGraphicContext; }
namespace GT { class IGraphicDevice; }

namespace GT { class IFileLoaderService; }
namespace GT { class IShaderLoaderService; }
namespace GT { class ITextureLoaderService; }
namespace GT { class IShaderManagerService; }
//END FORWARD DECL

namespace GT
{
	class IContext
	{
	public:
		IContext() {};
		virtual ~IContext() {};

		virtual IGraphicDevice& GetGraphicDevice() const = 0;
		virtual IGraphicContext& GetGraphicContext() const = 0;

		virtual IFileLoaderService& GetFileLoaderService() const = 0;
		virtual IShaderLoaderService& GetShaderLoaderService() const = 0;
		virtual ITextureLoaderService& GetTextureLoaderService() const = 0;
		virtual IShaderManagerService& GetShaderManagerService() const = 0;
	};
}