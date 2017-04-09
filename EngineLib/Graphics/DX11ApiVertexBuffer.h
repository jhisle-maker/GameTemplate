#pragma once

#include "IApiBufferWrapper.h"

//START FORWARD DECL
struct ID3D11Buffer;
//END FORWARD DECL

namespace GT
{
	class DX11ApiVertexBuffer : public IApiBufferWrapper
	{
	public:
		DX11ApiVertexBuffer(ID3D11Buffer* i_poD3D11Buffer);
		virtual ~DX11ApiVertexBuffer();

	public:
		inline ID3D11Buffer* const* GetD3D11BufferAddress() const { return &m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}