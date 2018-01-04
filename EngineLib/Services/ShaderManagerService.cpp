#include "ShaderManagerService.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\IVertexShader.h"
#include "Services\ShadersRegistryService.h"
#include "Services\IShaderLoaderService.h"
#include "VertexDeclarations\BasicVertexDeclarations.h"

namespace GT
{
	ShaderManagerService::ShaderManagerService(const IShaderLoaderService& i_oShaderLoaderService)
		: m_oShaderLoaderService(i_oShaderLoaderService)
	{
		//Nothing to do here
	}

	ShaderManagerService::~ShaderManagerService()
	{
		//Nothing to do here
	}

	void ShaderManagerService::LoadShaders(const ShadersRegistryService& i_oShadersRegistry)
	{ 
		m_oPixelShaderMap.clear();
		m_oVertexShaderMap.clear();

		size_t shaderCount = i_oShadersRegistry.GetSize();
		for (uint16_t uiIndex = 0u; uiIndex < shaderCount; ++uiIndex)
		{
			const ShaderDesc& shaderDesc = i_oShadersRegistry.GetShaderDesc(uiIndex);
			switch (shaderDesc.m_eShaderType)
			{
			case ShaderType::PIXEL:
				m_oPixelShaderMap[shaderDesc.m_oShaderId] = m_oShaderLoaderService.LoadPixelShader(shaderDesc.m_oPath);
				break;

			case ShaderType::VERTEX:
				m_oVertexShaderMap[shaderDesc.m_oShaderId] = m_oShaderLoaderService.LoadVertexShader(shaderDesc.m_oPath, *shaderDesc.m_oVertexDeclaration);
				break;
			}
		}
	}
}

