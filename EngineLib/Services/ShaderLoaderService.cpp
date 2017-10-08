#include "ShaderLoaderService.h"
#include "Services\IFileLoaderService.h"
#include "Graphics\VertexShader.h"
#include "Graphics\PixelShader.h"

#include <vector>
#include <memory>

namespace GT
{
	ShaderLoaderService::ShaderLoaderService(const IFileLoaderService& i_oFileLoaderService, const IGraphicContext& i_oGraphicContext)
		: m_oFileLoaderService(i_oFileLoaderService)
		, m_oGraphicContext(i_oGraphicContext)
	{
		//Nothing to do here
	}

	ShaderLoaderService::~ShaderLoaderService()
	{
		//Nothing to do here
	}


	std::unique_ptr<IPixelShader> ShaderLoaderService::LoadPixelShader(const std::string& i_oShaderId) const
	{
		std::vector<uint8_t> oShaderBuffer;
		m_oFileLoaderService.Load(i_oShaderId, oShaderBuffer);

		return std::make_unique<PixelShader>(oShaderBuffer, m_oGraphicContext);
	}

	std::unique_ptr<IVertexShader> ShaderLoaderService::LoadVertexShader(const std::string& i_oShaderId, const VertexDeclaration& i_oVertexDeclaration) const
	{
		std::vector<uint8_t> oShaderBuffer;
		m_oFileLoaderService.Load(i_oShaderId, oShaderBuffer);

		return std::make_unique<VertexShader>(oShaderBuffer, i_oVertexDeclaration, m_oGraphicContext);
	}
}