#pragma once

#include "IApiBufferWrapper.h"

//START FORWARD DECL
struct ID3D11Buffer;
//END FORWARD DECL

namespace GT
{
	class DX11ApiIndexBuffer : public IApiBufferWrapper
	{
	public:
		DX11ApiIndexBuffer(ID3D11Buffer* i_poD3D11Buffer);
		virtual ~DX11ApiIndexBuffer();

	public:
		inline ID3D11Buffer* GetD3D11Buffer() const { return m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}