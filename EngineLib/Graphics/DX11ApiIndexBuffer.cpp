#include "DX11ApiIndexBuffer.h"
#include <d3d11_3.h>

namespace GT
{
	DX11ApiIndexBuffer::DX11ApiIndexBuffer(ID3D11Buffer* i_poD3D11Buffer)
		: m_poBuffer(i_poD3D11Buffer)
	{
		//Nothing to do here
	}

	DX11ApiIndexBuffer::~DX11ApiIndexBuffer()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}