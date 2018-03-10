#pragma once

#include <memory>
#include <string>

//START FORWARD DECL
namespace GT { class IFile; }
namespace GT { class ITexture; }
namespace GT { class IVertexShader; }
namespace GT { struct VertexDeclaration; }
namespace GT { class IPixelShader; }
//END FORWARD DECL

namespace GT
{
	class IContentManager
	{
	public:
		IContentManager() {}
		virtual ~IContentManager() {}

	public:
		virtual std::unique_ptr<IFile> LoadFile(const std::string& i_ofilePath) const = 0;
		virtual ITexture& LoadTexture(const std::string& i_oTexturePath) = 0;
		virtual IVertexShader& LoadVertexShader(const std::string& i_oShaderPath, const VertexDeclaration& i_oVertexDeclaration) = 0;
		virtual IPixelShader& LoadPixelShader(const std::string& i_oShaderPath) = 0;
	};
}

