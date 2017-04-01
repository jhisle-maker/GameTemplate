#pragma once
#include "DX11GraphicContext.h"
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

	void DX11GraphicContext::CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount, void*& o_oApiVertexBuffer) const
	{
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = i_paoVertexData;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(static_cast<uint32_t>(i_uiVertexSize * i_uiElementsCount), D3D11_BIND_VERTEX_BUFFER);

		m_poDevice->CreateBuffer
		(
			&vertexBufferDesc,
			&vertexBufferData,
			reinterpret_cast<ID3D11Buffer**>(&o_oApiVertexBuffer)
		);
	}

	void DX11GraphicContext::CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount, void*& o_oApiIndexBuffer) const
	{
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = i_paoIndexData;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC indexBufferDesc(static_cast<uint32_t>(i_uiIndexSize * i_uiElementsCount), D3D11_BIND_INDEX_BUFFER);
		
		m_poDevice->CreateBuffer
		(
			&indexBufferDesc,
			&indexBufferData,
			reinterpret_cast<ID3D11Buffer**>(&o_oApiIndexBuffer)
		);
	}

	void DX11GraphicContext::ReleaseApiVertexBuffer(void*& i_oApiVertexBuffer) const
	{
		if(i_oApiVertexBuffer != nullptr)
		{ 
			reinterpret_cast<ID3D11Buffer*>(i_oApiVertexBuffer)->Release();
		}
	}
	
	void DX11GraphicContext::ReleaseApiIndexBuffer(void*& i_oApiIndexBuffer) const
	{
		if (i_oApiIndexBuffer != nullptr)
		{
			reinterpret_cast<ID3D11Buffer*>(i_oApiIndexBuffer)->Release();
		}
	}
}
