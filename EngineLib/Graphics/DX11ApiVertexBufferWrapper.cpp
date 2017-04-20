#include "DX11ApiVertexBufferWrapper.h"
#include <d3d11_3.h>

namespace GT
{
	DX11ApiVertexBufferWrapper::DX11ApiVertexBufferWrapper(ID3D11Buffer& i_oD3D11Buffer) 
		: m_poBuffer(&i_oD3D11Buffer) 
	{ 
		//Nothing to do here
	}

	DX11ApiVertexBufferWrapper::~DX11ApiVertexBufferWrapper()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}