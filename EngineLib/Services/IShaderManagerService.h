#pragma once

//START FORWARD DECL
namespace GT
{
	class IPixelShader;
	class IVertexShader;
	class IShaderLoaderService;
}
//END FORWARD DECL

namespace GT
{
	class IShaderManagerService
	{
	public:
		IShaderManagerService() {}
		virtual ~IShaderManagerService() {}

	public:
		virtual void LoadShaders() = 0;

		virtual const IPixelShader& GetPositionColorPS() const = 0;
		virtual const IVertexShader& GetPositionColorVS() const = 0;
		virtual const IPixelShader& GetPositionColorTexturePS() const = 0;
		virtual const IVertexShader& GetPositionColorTextureVS() const = 0;
	};
}