#include "DX11ApiVertexBufferWrapper.h"
#include <d3d11_3.h>
#include <cstdint>

namespace GT
{
	DX11ApiVertexBufferWrapper::DX11ApiVertexBufferWrapper(ID3D11Device& i_oDevice, const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount)
		: m_poBuffer(nullptr) 
	{ 
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = i_paoVertexData;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(static_cast<uint32_t>(i_uiVertexSize * i_uiElementsCount), D3D11_BIND_VERTEX_BUFFER);

		i_oDevice.CreateBuffer
		(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_poBuffer
		);
	}

	DX11ApiVertexBufferWrapper::~DX11ApiVertexBufferWrapper()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}