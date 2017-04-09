#include "DX11ApiVertexBuffer.h"
#include <d3d11_3.h>

namespace GT
{
	DX11ApiVertexBuffer::DX11ApiVertexBuffer(ID3D11Buffer* i_poD3D11Buffer) 
		: m_poBuffer(i_poD3D11Buffer) 
	{ 
		//Nothing to do here
	}

	DX11ApiVertexBuffer::~DX11ApiVertexBuffer()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}