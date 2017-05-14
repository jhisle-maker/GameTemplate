#include "DX11ApiIndexBufferWrapper.h"
#include <d3d11_3.h>
#include <cstdint>

namespace GT
{
	DX11ApiIndexBufferWrapper::DX11ApiIndexBufferWrapper(ID3D11Device& i_oDevice, const void* i_paoIndexData, size_t i_uiIndexSize, size_t i_uiElementsCount)
		: m_poBuffer(nullptr)
	{
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = i_paoIndexData;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC indexBufferDesc(static_cast<uint32_t>(i_uiIndexSize * i_uiElementsCount), D3D11_BIND_INDEX_BUFFER);

		i_oDevice.CreateBuffer
		(
			&indexBufferDesc,
			&indexBufferData,
			&m_poBuffer
		);
	}

	DX11ApiIndexBufferWrapper::~DX11ApiIndexBufferWrapper()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}