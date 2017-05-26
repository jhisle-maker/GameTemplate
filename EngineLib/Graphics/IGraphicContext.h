#pragma once
#include <memory>
#include <string>
#include <vector>

#include "VertexDeclaration.h"

//START FORWARD DECL
namespace GT { class IApiGraphicResource; }
//END FORWARD DECL

namespace GT
{
	class IGraphicContext
	{
	public:
		virtual ~IGraphicContext() { }
		virtual std::unique_ptr<IApiGraphicResource> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiGraphicResource> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiGraphicResource> CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const = 0;
		virtual std::unique_ptr<IApiGraphicResource> CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const = 0;
		virtual std::unique_ptr<IApiGraphicResource> CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const = 0;
		virtual std::unique_ptr<IApiGraphicResource> CreateApiTexture2D(const void* i_paoTextureData, const size_t i_uiWidth, const size_t i_uiHeight) const = 0;

		virtual void UpdateApiConstantBuffer(const IApiGraphicResource& constBufferWrapper, const void* i_poUpdateData) const = 0;
	};
}

