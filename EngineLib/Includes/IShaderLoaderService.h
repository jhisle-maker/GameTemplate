#pragma once

#include<string>
#include<memory>

//START FORWARD DELCS
namespace GT { class IVertexShader; }
namespace GT { class IPixelShader; }
namespace GT { struct VertexDeclaration; }
//END FORWARD DECLS

namespace GT
{
	class IShaderLoaderService
	{
	public:
		IShaderLoaderService() {};
		virtual ~IShaderLoaderService() {}

	public:
		virtual std::unique_ptr<IVertexShader> LoadVertexShader(const std::string& i_oShaderPath, const VertexDeclaration& i_oVertexDeclaration) const = 0;
		virtual std::unique_ptr<IPixelShader> LoadPixelShader(const std::string& i_oShaderPath) const = 0;
	};
}