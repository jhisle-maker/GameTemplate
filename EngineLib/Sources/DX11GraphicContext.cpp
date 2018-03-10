#pragma once
#include "DX11GraphicContext.h"
#include "DX11ApiVertexBufferWrapper.h"
#include "DX11ApiIndexBufferWrapper.h"
#include "DX11ApiConstantBufferWrapper.h"
#include "DX11ApiVertexShaderWrapper.h"
#include "DX11ApiPixelShaderWrapper.h"
#include "DX11ApiTexture2DWrapper.h"
#include "DX11ApiSamplerStateWrapper.h"
#include "Color.h"

#include <vector>
#include <wrl/client.h>
#include <d3d11_3.h>
#include <stdint.h>

namespace GT
{
	DX11GraphicContext::DX11GraphicContext(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice, const Microsoft::WRL::ComPtr<ID3D11DeviceContext3> i_poContext)
		: m_poDevice(i_poDevice)
		, m_poContext(i_poContext)
	{
		//Nothing to do here
	}

	DX11GraphicContext::~DX11GraphicContext()
	{
		//Nothing to do here
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const
	{
		return std::move(std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiVertexBufferWrapper(*m_poDevice.Get(), i_paoVertexData, i_uiVertexSize, i_uiElementsCount)));
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const
	{
		return std::move(std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiIndexBufferWrapper(*m_poDevice.Get(), i_paoIndexData, i_uiIndexSize, i_uiElementsCount)));
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const
	{
		return std::move(std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiConstantBufferWrapper(*m_poDevice.Get(), i_poData, i_uiDataSize)));
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const
	{
		return std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiVertexShaderWrapper(*m_poDevice.Get(), i_oShaderFileBytes, vertexDeclaration));
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const
	{
		return std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiPixelShaderWrapper(*m_poDevice.Get(), i_oShaderFileBytes));
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiTexture2D(const std::vector<Color>& i_aoTextureData, const size_t i_uiWidth, const size_t i_uiHeight) const
	{
		return std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiTexture2DWrapper(*m_poDevice.Get(), i_aoTextureData.data(), i_uiWidth, i_uiHeight));
	}

	std::unique_ptr<IApiGraphicResourceWrapper> DX11GraphicContext::CreateApiSamplerState() const
	{
		return std::unique_ptr<IApiGraphicResourceWrapper>(new DX11ApiSamplerStateWrapper(*m_poDevice.Get()));
	}

	void DX11GraphicContext::UpdateApiConstantBuffer(const IApiGraphicResourceWrapper& constBufferWrapper, const void* i_poUpdateData) const
	{
		const DX11ApiConstantBufferWrapper& apiWrapper = static_cast<const DX11ApiConstantBufferWrapper&>(constBufferWrapper);
		m_poContext->UpdateSubresource1(apiWrapper.GetD3D11BufferPtr(), 0, nullptr, i_poUpdateData, 0, 0, 0);
	}

	void DX11GraphicContext::BindVertexShaderConstBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper) const
	{
		const DX11ApiConstantBufferWrapper& oApiBuffer = static_cast<const DX11ApiConstantBufferWrapper&>(i_oConstBufferApiWrapper);
		m_poContext->VSSetConstantBuffers(0, 1, oApiBuffer.GetD3D11BufferPtrAddress());
	}

	void DX11GraphicContext::BindPixelShaderConstBuffer(const IApiGraphicResourceWrapper& i_oConstBufferApiWrapper) const
	{
		const DX11ApiConstantBufferWrapper& oApiBuffer = static_cast<const DX11ApiConstantBufferWrapper&>(i_oConstBufferApiWrapper);
		m_poContext->PSSetConstantBuffers(0, 1, oApiBuffer.GetD3D11BufferPtrAddress());
	}

	void DX11GraphicContext::BindVertexShaderTexture(const IApiGraphicResourceWrapper& i_oTextureApiWrapper) const
	{
		const DX11ApiTexture2DWrapper& oApiTexture2D = static_cast<const DX11ApiTexture2DWrapper&>(i_oTextureApiWrapper);
		m_poContext->VSSetShaderResources(0, 1, oApiTexture2D.GetSRVAddress());
	}
		
	void DX11GraphicContext::BindPixelShaderTexture(const IApiGraphicResourceWrapper& i_oTextureApiWrapper) const
	{
		const DX11ApiTexture2DWrapper& oApiTexture2D = static_cast<const DX11ApiTexture2DWrapper&>(i_oTextureApiWrapper);
		m_poContext->PSSetShaderResources(0, 1, oApiTexture2D.GetSRVAddress());
	}

	void DX11GraphicContext::BindPixelShaderSampler(const IApiGraphicResourceWrapper& i_oSampler) const
	{
		const DX11ApiSamplerStateWrapper& oSamplerState = static_cast<const DX11ApiSamplerStateWrapper&>(i_oSampler);
		m_poContext->PSSetSamplers(0, 1, oSamplerState.GetSamplerStateAddress());
	}
}
