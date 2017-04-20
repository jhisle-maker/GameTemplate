#pragma once
#include "IApiPixelShaderWrapper.h"
#include <d3d11_4.h>

namespace GT
{
	class DX11ApiPixelShaderWrapper : public IApiPixelShaderWrapper
	{
	public:
		DX11ApiPixelShaderWrapper(ID3D11PixelShader& i_poPixelShader);
		~DX11ApiPixelShaderWrapper();

	public:
		ID3D11PixelShader* GetDX11PixelShader() const { return m_poPixelShader; }

	private:
		ID3D11PixelShader* m_poPixelShader;
	};
}