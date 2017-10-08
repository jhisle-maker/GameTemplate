#pragma once
#include <memory>
#include <string>
#include <vector>

#include "VertexDeclaration.h"
#include "Color.h"

//START FORWARD DECL
namespace GT { class IApiGraphicResourceWrapper; }
//END FORWARD DECL

namespace GT
{
	class IGraphicContext
	{
	public:
		IGraphicContext() {}
		virtual ~IGraphicContext() { }
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const = 0;
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const = 0;
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const = 0;
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiTexture2D(const std::vector<Color>& i_aoTextureData, const size_t i_uiWidth, const size_t i_uiHeight) const = 0;
		virtual std::unique_ptr<IApiGraphicResourceWrapper> CreateApiSamplerState() const = 0;

		virtual void UpdateApiConstantBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper, const void* i_poUpdateData) const = 0;
		virtual void BindVertexShaderConstBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper) const = 0;
		virtual void BindPixelShaderConstBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper) const = 0;

		virtual void BindVertexShaderTexture(const IApiGraphicResourceWrapper& i_oTexture) const = 0;
		virtual void BindPixelShaderTexture(const IApiGraphicResourceWrapper& i_oTexture) const = 0;

		virtual void BindPixelShaderSampler(const IApiGraphicResourceWrapper& i_oSampler) const = 0;
	};
}

