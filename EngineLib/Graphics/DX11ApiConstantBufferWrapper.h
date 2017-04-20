#pragma once
#include <d3d11_3.h>
#include "IApiBufferWrapper.h"

namespace GT
{
	class DX11ApiConstantBufferWrapper : public IApiBufferWrapper
	{
	public:
		DX11ApiConstantBufferWrapper(ID3D11Buffer& i_oD3D11Buffer);
		~DX11ApiConstantBufferWrapper();

	public:
		inline ID3D11Buffer* GetD3D11BufferPtr() const { return m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}
