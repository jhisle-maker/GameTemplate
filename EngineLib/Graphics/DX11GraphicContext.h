#pragma once
#include <wrl/client.h>
#include <d3d11_3.h>
#include "IGraphicContext.h"

//START FORWARD DECLS
namespace GT { class IApiGraphicResourceWrapper; }
//END FORWARD DECLS

namespace GT
{
	class DX11GraphicContext : public IGraphicContext
	{
	public:
		DX11GraphicContext(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice, const Microsoft::WRL::ComPtr<ID3D11DeviceContext3> i_poContext);
		virtual ~DX11GraphicContext();

	public:
		std::unique_ptr<IApiGraphicResourceWrapper> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const;
		std::unique_ptr<IApiGraphicResourceWrapper> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const;
		std::unique_ptr<IApiGraphicResourceWrapper> CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const;
		std::unique_ptr<IApiGraphicResourceWrapper> CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const;
		std::unique_ptr<IApiGraphicResourceWrapper> CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const;
		std::unique_ptr<IApiGraphicResourceWrapper> CreateApiTexture2D(const std::vector<Color>& i_aoTextureData, const size_t i_uiWidth, const size_t i_uiHeight) const;

		void UpdateApiConstantBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper, const void* i_poUpdateData) const;
		void BindVertexShaderConstBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper) const;
		void BindPixelShaderConstBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper) const;
		
		void BindVertexShaderTexture(const IApiGraphicResourceWrapper& i_oTexture) const;
		void BindPixelShaderTexture(const IApiGraphicResourceWrapper& i_oTexture) const;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_poDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext3> m_poContext;
	};
}
