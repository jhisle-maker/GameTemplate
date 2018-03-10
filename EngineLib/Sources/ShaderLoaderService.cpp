#include "ShaderLoaderService.h"
#include "IFileLoaderService.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IFile.h"

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
		std::unique_ptr<IFile> shaderFile = m_oFileLoaderService.Load(i_oShaderId);
		return std::make_unique<PixelShader>(shaderFile->GetData(), m_oGraphicContext);
	}

	std::unique_ptr<IVertexShader> ShaderLoaderService::LoadVertexShader(const std::string& i_oShaderId, const VertexDeclaration& i_oVertexDeclaration) const
	{
		std::unique_ptr<IFile> shaderFile = m_oFileLoaderService.Load(i_oShaderId);
		return std::make_unique<VertexShader>(shaderFile->GetData(), i_oVertexDeclaration, m_oGraphicContext);
	}
}