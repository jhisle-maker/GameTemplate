#pragma once
#include <d3d11_3.h>
#include "IApiGraphicResourceWrapper.h"

namespace GT
{
	class DX11ApiSamplerStateWrapper : public IApiGraphicResourceWrapper
	{
	public:
		DX11ApiSamplerStateWrapper(ID3D11Device& i_oDevice);
		virtual ~DX11ApiSamplerStateWrapper();

	public:
		inline ID3D11SamplerState* const* GetSamplerStateAddress() const { return &m_poSamplerState; }

	private:
		ID3D11SamplerState* m_poSamplerState;
	};
}
