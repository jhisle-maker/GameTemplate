#pragma once
#include <memory>
#include <string>
#include <vector>

#include "VertexDeclaration.h"

//START FORWARD DECL
namespace GT { class IApiBufferWrapper; }
namespace GT { class IApiPixelShaderWrapper; }
namespace GT { class IApiVertexShaderWrapper; }
//END FORWARD DECL

namespace GT
{
	class IGraphicContext
	{
	public:
		virtual ~IGraphicContext() { }
		virtual std::unique_ptr<IApiBufferWrapper> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiBufferWrapper> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiBufferWrapper> CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const = 0;
		virtual std::unique_ptr<IApiVertexShaderWrapper> CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const = 0;
		virtual std::unique_ptr<IApiPixelShaderWrapper> CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const = 0;

		virtual void UpdateApiConstantBuffer(const IApiBufferWrapper& constBufferWrapper, const void* i_poUpdateData) const = 0;
	};
}

