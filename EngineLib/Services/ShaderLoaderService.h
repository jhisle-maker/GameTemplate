#pragma once

#include "IShaderLoaderService.h"

//START FORWARD DECL
namespace GT { class IFileLoaderService; }
namespace GT { class IGraphicContext; }
//END FORWARD DECL

namespace GT
{
	class ShaderLoaderService : public IShaderLoaderService
	{
	public:
		ShaderLoaderService(const IFileLoaderService& i_oFileLoaderService, const IGraphicContext& i_oGraphicContext);
		~ShaderLoaderService();

	public:
		std::unique_ptr<IVertexShader> LoadVertexShader(const std::string& i_oShaderPath, const VertexDeclaration& i_oVertexDeclaration) const;
		std::unique_ptr<IPixelShader> LoadPixelShader(const std::string& i_oShaderId) const;

	private:
		ShaderLoaderService(const ShaderLoaderService& i_oOther) = delete;
		ShaderLoaderService& operator=(const ShaderLoaderService& i_oOther) = delete;

	private:
		const IFileLoaderService& m_oFileLoaderService;
		const IGraphicContext& m_oGraphicContext;
	};
}