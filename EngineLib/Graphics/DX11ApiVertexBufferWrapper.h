#pragma once
#include <d3d11_3.h>
#include "IApiGraphicResource.h"

namespace GT
{
	class DX11ApiVertexBufferWrapper : public IApiGraphicResource
	{
	public:
		DX11ApiVertexBufferWrapper(ID3D11Device& i_oDevice, const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount);
		virtual ~DX11ApiVertexBufferWrapper();

	public:
		inline ID3D11Buffer* GetD3D11BufferPtr() const { return m_poBuffer; }
		inline ID3D11Buffer* const* GetD3D11BufferPtrAddress() const { return &m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}