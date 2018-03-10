#include "DX11ApiConstantBufferWrapper.h"

namespace GT
{
	DX11ApiConstantBufferWrapper::DX11ApiConstantBufferWrapper(ID3D11Device& i_oD3D11Device, const void* i_poData, size_t i_uiDataSize)
		: m_poBuffer(nullptr)
	{
		CD3D11_BUFFER_DESC constantBufferDesc(static_cast<UINT>(i_uiDataSize), D3D11_BIND_CONSTANT_BUFFER);
		
		D3D11_SUBRESOURCE_DATA oInitialData;
		oInitialData.pSysMem = i_poData;
		oInitialData.SysMemPitch = 0;
		oInitialData.SysMemSlicePitch = 0;

		i_oD3D11Device.CreateBuffer(&constantBufferDesc, &oInitialData, &m_poBuffer);
	}

	DX11ApiConstantBufferWrapper::~DX11ApiConstantBufferWrapper()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}