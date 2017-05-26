#pragma once
#include <wrl/client.h>
#include <d3d11_3.h>
#include "IGraphicContext.h"

//START FORWARD DECLS
namespace GT { class IApiGraphicResource; }
//END FORWARD DECLS

namespace GT
{
	class DX11GraphicContext : public IGraphicContext
	{
	public:
		DX11GraphicContext(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice, const Microsoft::WRL::ComPtr<ID3D11DeviceContext3> i_poContext);
		virtual ~DX11GraphicContext();

	public:
		std::unique_ptr<IApiGraphicResource> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const;
		std::unique_ptr<IApiGraphicResource> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const;
		std::unique_ptr<IApiGraphicResource> CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const;
		std::unique_ptr<IApiGraphicResource> CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& verteDeclaration) const;
		std::unique_ptr<IApiGraphicResource> CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const;
		std::unique_ptr<IApiGraphicResource> CreateApiTexture2D(const void* i_paoTextureData, const size_t i_uiWidth, const size_t i_uiHeight) const;

		void UpdateApiConstantBuffer(const IApiGraphicResource& constBufferWrapper, const void* i_poUpdateData) const;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_poDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext3> m_poContext;
	};
}
