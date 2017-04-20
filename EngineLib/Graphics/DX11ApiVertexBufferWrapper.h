#pragma once
#include <d3d11_3.h>
#include "IApiBufferWrapper.h"

namespace GT
{
	class DX11ApiVertexBufferWrapper : public IApiBufferWrapper
	{
	public:
		DX11ApiVertexBufferWrapper(ID3D11Buffer& i_oD3D11Buffer);
		virtual ~DX11ApiVertexBufferWrapper();

	public:
		inline ID3D11Buffer* GetD3D11BufferPtr() const { return m_poBuffer; }
		inline ID3D11Buffer* const* GetD3D11BufferPtrAddress() const { return &m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}