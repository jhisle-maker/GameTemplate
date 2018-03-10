#pragma once

#include "IApiGraphicResourceWrapper.h"
#include <d3d11_3.h>

namespace GT
{
	class DX11ApiTexture2DWrapper : public IApiGraphicResourceWrapper
	{
	public:
		DX11ApiTexture2DWrapper(ID3D11Device& i_oDevice, const void* i_paoData, const size_t i_uiWidth, const size_t i_uiHeight);
		~DX11ApiTexture2DWrapper();

	public:
		ID3D11Texture2D* GetDX11Texture2D() const { return m_poTexture2D; }
		ID3D11ShaderResourceView* const* GetSRVAddress() const { return &m_poTexture2DSRV; }

	private:
		DX11ApiTexture2DWrapper(const DX11ApiTexture2DWrapper& i_oOther) {};
		DX11ApiTexture2DWrapper& operator=(const DX11ApiTexture2DWrapper& i_oOther) {};

	private:
		ID3D11Texture2D* m_poTexture2D;
		ID3D11ShaderResourceView* m_poTexture2DSRV;
	};
}
