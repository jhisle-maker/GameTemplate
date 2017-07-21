#pragma once
#include <wrl/client.h>
#include <d3d11_4.h>
#include <vector>

#include "IApiGraphicResourceWrapper.h"

namespace GT
{
	class DX11ApiPixelShaderWrapper : public IApiGraphicResourceWrapper
	{
	public:
		DX11ApiPixelShaderWrapper(ID3D11Device& i_oDevice, const std::vector<uint8_t>& i_oShaderFileBytes);
		~DX11ApiPixelShaderWrapper();

	public:
		ID3D11PixelShader* GetDX11PixelShader() const { return m_poPixelShader; }

	private:
		ID3D11PixelShader* m_poPixelShader;
	};
}