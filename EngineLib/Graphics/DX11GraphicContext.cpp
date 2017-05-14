#pragma once
#include "Utils\Utils.h"
#include "DX11GraphicContext.h"
#include "DX11ApiVertexBufferWrapper.h"
#include "DX11ApiIndexBufferWrapper.h"
#include "DX11ApiConstantBufferWrapper.h"
#include "DX11ApiVertexShaderWrapper.h"
#include "DX11ApiPixelShaderWrapper.h"

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

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const
	{
		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiVertexBufferWrapper(*m_poDevice.Get(), i_paoVertexData, i_uiVertexSize, i_uiElementsCount)));
	}

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const
	{
		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiIndexBufferWrapper(*m_poDevice.Get(), i_paoIndexData, i_uiIndexSize, i_uiElementsCount)));
	}

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiConstantBuffer(const void* i_poData, const size_t i_uiDataSize) const
	{
		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiConstantBufferWrapper(*m_poDevice.Get(), i_poData, i_uiDataSize)));
	}

	std::unique_ptr<IApiVertexShaderWrapper> DX11GraphicContext::CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const
	{
		return std::unique_ptr<IApiVertexShaderWrapper>(new DX11ApiVertexShaderWrapper(*m_poDevice.Get(), i_oShaderFileBytes, vertexDeclaration));
	}

	std::unique_ptr<IApiPixelShaderWrapper> DX11GraphicContext::CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const
	{
		return std::unique_ptr<IApiPixelShaderWrapper>(new DX11ApiPixelShaderWrapper(*m_poDevice.Get(), i_oShaderFileBytes));
	}

	void DX11GraphicContext::UpdateApiConstantBuffer(const IApiBufferWrapper& constBufferWrapper, const void* i_poUpdateData) const
	{
		const DX11ApiConstantBufferWrapper& apiWrapper = static_cast<const DX11ApiConstantBufferWrapper&>(constBufferWrapper);
		m_poContext->UpdateSubresource1(apiWrapper.GetD3D11BufferPtr(), 0, nullptr, i_poUpdateData, 0, 0, 0);
	}
}
