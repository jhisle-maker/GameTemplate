#pragma once

//START FORWARD DECL
namespace GT { class IContext; }

namespace GT { class IGraphicContext; }
namespace GT { class IGraphicDevice; }

namespace GT { class IFileLoaderService; }
namespace GT { class IShaderLoaderService; }
namespace GT { class ITextureLoaderService; }
namespace GT { class IShaderManagerService; }
//END FORWARD DECL

namespace GT
{
	class BaseComponent
	{
	public:
		BaseComponent(const IContext& context);
		virtual ~BaseComponent() {};

	private:
		IGraphicContext& m_oGraphicContext;
		IGraphicDevice& m_oGraphicDevice;

		IFileLoaderService& m_oFileLoader;
		ITextureLoaderService& m_oTextureLoader;
		IShaderManagerService& m_oShaderManager;
	};
}
