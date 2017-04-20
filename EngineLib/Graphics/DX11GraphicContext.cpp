#pragma once
#include "Utils\Utils.h"
#include "DX11GraphicContext.h"
#include "DX11ApiVertexBufferWrapper.h"
#include "DX11ApiIndexBufferWrapper.h"
#include "DX11ApiVertexShaderWrapper.h"
#include "DX11ApiPixelShaderWrapper.h"

#include <vector>
#include <wrl/client.h>
#include <d3d11_3.h>
#include <stdint.h>

namespace GT
{
	DX11GraphicContext::DX11GraphicContext(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice)
		: m_poDevice(i_poDevice)
	{
		//Nothing to do here
	}

	DX11GraphicContext::~DX11GraphicContext()
	{
		//Nothing to do here
	}

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const
	{
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = i_paoVertexData;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(static_cast<uint32_t>(i_uiVertexSize * i_uiElementsCount), D3D11_BIND_VERTEX_BUFFER);

		ID3D11Buffer* poBuffer = nullptr;
		m_poDevice->CreateBuffer
		(
			&vertexBufferDesc,
			&vertexBufferData,
			&poBuffer
		);

		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiVertexBufferWrapper(*poBuffer)));
	}

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const
	{
		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiIndexBufferWrapper(m_poDevice, i_paoIndexData, i_uiIndexSize, i_uiElementsCount)));
	}

	std::unique_ptr<IApiVertexShaderWrapper> DX11GraphicContext::CreateApiVertexShader(const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration) const
	{
		ID3D11VertexShader* poVertexShader = nullptr;
		m_poDevice->CreateVertexShader
		(
			i_oShaderFileBytes.data(),
			i_oShaderFileBytes.size(),
			nullptr,
			reinterpret_cast<ID3D11VertexShader**>(&poVertexShader)
		);

		std::vector<D3D11_INPUT_ELEMENT_DESC> vertexDescArray;
		vertexDescArray.reserve(vertexDeclaration.VertexDeclarationItemsCount);

		UINT alignedByteOffset = 0;
		for (int index = 0; index < vertexDeclaration.VertexDeclarationItemsCount; ++index)
		{
			char* semanticName = nullptr;
			DXGI_FORMAT format;
			UINT formatByteSize = 0;

			VertexDeclarationItem vertexDeclarationItem = vertexDeclaration.VertexDeclarationItems[index];
			switch (vertexDeclarationItem.Type)
			{
				case FLOAT32:
					format = DXGI_FORMAT_R32G32B32_FLOAT;
					formatByteSize = 12;
					break;
			}

			switch (vertexDeclarationItem.Usage)
			{
				case POSITION:
					semanticName = "POSITION";
					break;
				case COLOR:
					semanticName = "COLOR";
					break;
				case TEXTURE:
					semanticName = "TEXTURE";
					break;
				case NORMAL:
					semanticName = "NORMAL";
					break;
			}

			vertexDescArray.push_back({ semanticName, 0, format, 0, alignedByteOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
			alignedByteOffset += formatByteSize;
		}

		ID3D11InputLayout* poInputLayout = nullptr;
		m_poDevice->CreateInputLayout
		(
			vertexDescArray.data(),
			static_cast<UINT>(vertexDescArray.size()),
			i_oShaderFileBytes.data(),
			i_oShaderFileBytes.size(),
			&poInputLayout
		);

		return std::unique_ptr<IApiVertexShaderWrapper>(new DX11ApiVertexShaderWrapper(*poVertexShader, *poInputLayout));
	}

	std::unique_ptr<IApiPixelShaderWrapper> DX11GraphicContext::CreateApiPixelShader(const std::vector<uint8_t>& i_oShaderFileBytes) const
	{
		ID3D11PixelShader* poPixelShader = nullptr;
		m_poDevice->CreatePixelShader(i_oShaderFileBytes.data(), i_oShaderFileBytes.size(), nullptr, &poPixelShader);

		return std::unique_ptr<IApiPixelShaderWrapper>(new DX11ApiPixelShaderWrapper(*poPixelShader));
	} 
}
