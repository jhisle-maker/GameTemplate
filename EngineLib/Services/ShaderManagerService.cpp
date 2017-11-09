#include "ShaderManagerService.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\IVertexShader.h"
#include "Services\IShaderLoaderService.h"
#include "VertexDeclarations\BasicVertexDeclarations.h"

namespace GT
{
	ShaderManagerService::ShaderManagerService(const IShaderLoaderService& i_oShaderLoaderService)
		: m_oShaderLoaderService(i_oShaderLoaderService)
		, i_poPositionColorPS(nullptr)
		, i_poPositionColorVS(nullptr)
		, i_poPositionColorTexturePS(nullptr)
		, i_poPositionColorTextureVS(nullptr)
	{
		//Nothing to do here
	}

	ShaderManagerService::~ShaderManagerService()
	{
		//Nothing to do here
	}

	void ShaderManagerService::LoadShaders()
	{ 
		i_poPositionColorPS = m_oShaderLoaderService.LoadPixelShader("SamplePixelShader.cso");
		i_poPositionColorVS = m_oShaderLoaderService.LoadVertexShader("SampleVertexShader.cso", VertexPositionColor::VertexDeclaration);
		i_poPositionColorTexturePS = m_oShaderLoaderService.LoadPixelShader("PositionColorTexturePixelShader.cso");
		i_poPositionColorTextureVS = m_oShaderLoaderService.LoadVertexShader("PositionColorTextureVertexShader.cso", VertexPositionColorTexture::VertexDeclaration);
	}
}

