#include "DX11ApiPixelShaderWrapper.h"

GT::DX11ApiPixelShaderWrapper::DX11ApiPixelShaderWrapper(ID3D11Device& i_oDevice, const std::vector<uint8_t>& i_oShaderFileBytes)
	: m_poPixelShader(nullptr)
{
	i_oDevice.CreatePixelShader(i_oShaderFileBytes.data(), i_oShaderFileBytes.size(), nullptr, &m_poPixelShader);
}

GT::DX11ApiPixelShaderWrapper::~DX11ApiPixelShaderWrapper()
{
	if (m_poPixelShader != nullptr)
	{
		m_poPixelShader->Release();
	}
}