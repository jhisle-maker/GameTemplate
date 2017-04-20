#pragma once
#include <wrl/client.h>
#include <d3d11_3.h>
#include "IApiBufferWrapper.h"

//START FORWARD DECL
struct ID3D11Buffer;
//END FORWARD DECL

namespace GT
{
	class DX11ApiIndexBufferWrapper : public IApiBufferWrapper
	{
	public:
		DX11ApiIndexBufferWrapper(Microsoft::WRL::ComPtr<ID3D11Device> m_poDevice, const void* i_paoIndexData, size_t i_uiIndexSize, size_t i_uiElementsCount);
		virtual ~DX11ApiIndexBufferWrapper();

	public:
		inline ID3D11Buffer* GetD3D11BufferPtr() const { return m_poBuffer; }

	private:
		ID3D11Buffer* m_poBuffer;
	};
}