#include "ShaderManagerService.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\IVertexShader.h"
#include "Services\IShaderLoaderService.h"
#include "VertexDeclarations\BasicVertexDeclarations.h"

namespace GT
{
	ShaderManagerService::ShaderManagerService(const IShaderLoaderService& i_oShaderLoaderService)
		: m_oShaderLoaderService(i_oShaderLoaderService)
		, m_poPositionColorPS(nullptr)
		, m_poPositionColorVS(nullptr)
		, m_poPositionColorTexturePS(nullptr)
		, m_poPositionColorTextureVS(nullptr)
	{
		//Nothing to do here
	}

	ShaderManagerService::~ShaderManagerService()
	{
		//Nothing to do here
	}

	void ShaderManagerService::LoadShaders(const std::map<std::string, std::string>& i_oShaderFileRegistry)
	{ 
		m_poPositionColorPS = m_oShaderLoaderService.LoadPixelShader(i_oShaderFileRegistry.at("SamplePixelShader"));
		m_poPositionColorVS = m_oShaderLoaderService.LoadVertexShader(i_oShaderFileRegistry.at("SampleVertexShader"), VertexPositionColor::VertexDeclaration);
		m_poPositionColorTexturePS = m_oShaderLoaderService.LoadPixelShader(i_oShaderFileRegistry.at("PositionColorTexturePixelShader"));
		m_poPositionColorTextureVS = m_oShaderLoaderService.LoadVertexShader(i_oShaderFileRegistry.at("PositionColorTextureVertexShader"), VertexPositionColorTexture::VertexDeclaration);
	}
}

