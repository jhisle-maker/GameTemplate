#pragma once

#include <map>
#include <string>

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
		virtual void LoadShaders(const std::map<std::string, std::string>& i_oShaderFileRegistry) = 0;

		virtual const IPixelShader& GetPositionColorPS() const = 0;
		virtual const IVertexShader& GetPositionColorVS() const = 0;
		virtual const IPixelShader& GetPositionColorTexturePS() const = 0;
		virtual const IVertexShader& GetPositionColorTextureVS() const = 0;
	};
}