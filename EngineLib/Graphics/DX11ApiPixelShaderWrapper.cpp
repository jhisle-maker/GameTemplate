#include "DX11ApiPixelShaderWrapper.h"

GT::DX11ApiPixelShaderWrapper::DX11ApiPixelShaderWrapper(ID3D11PixelShader& i_oPixelShader)
	: m_poPixelShader(&i_oPixelShader)
{
	//Nothing to do here
}

GT::DX11ApiPixelShaderWrapper::~DX11ApiPixelShaderWrapper()
{
	if (m_poPixelShader != nullptr)
	{
		m_poPixelShader->Release();
	}
}