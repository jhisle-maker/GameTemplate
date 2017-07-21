#pragma once
#include <d3d11_3.h>
#include "IApiGraphicResourceWrapper.h"

namespace GT
{
	class DX11ApiConstantBufferWrapper : public IApiGraphicResourceWrapper
	{
	public:
		DX11ApiConstantBufferWrapper(ID3D11Device& i_oDevice, const void* i_poData, size_t i_uiDataSize);
		~DX11ApiConstantBufferWrapper();

	public:
		inline ID3D11Buffer* GetD3D11BufferPtr() const { return m_poBuffer; }
		inline ID3D11Buffer* const* GetD3D11BufferPtrAddress() const { return &m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}
