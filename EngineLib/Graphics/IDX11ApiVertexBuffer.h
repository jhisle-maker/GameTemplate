#pragma once

#include "IApiVertexBuffer.h"

//START FORWARD DECL
struct ID3D11Buffer;
//END FORWARD DECL

namespace GT
{
	class IDX11ApiVertexBuffer : public IApiVertexBuffer
	{
	public:
		IDX11ApiVertexBuffer(ID3D11Buffer* i_poD3D11Buffer) : m_poBuffer(i_poD3D11Buffer) { }
		virtual ~IDX11ApiVertexBuffer() 
		{ 
			if (m_poBuffer != nullptr) m_poBuffer->Release(); 
		}

	public:
		inline ID3D11Buffer* const* GetD3D11BufferAddress() const { return &m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}