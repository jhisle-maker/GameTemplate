#include "DX11ApiSamplerStateWrapper.h"
#include "Logger\Logger.h"
#include "Utils\Common.h"

namespace GT
{
	DX11ApiSamplerStateWrapper::DX11ApiSamplerStateWrapper(ID3D11Device& i_oDevice)
	{
		D3D11_SAMPLER_DESC samplerDesc;
		memset(&samplerDesc, 0u, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		samplerDesc.MinLOD = -D3D11_FLOAT32_MAX;

		HRESULT hr = i_oDevice.CreateSamplerState(&samplerDesc, &m_poSamplerState);
		GTASSERTL(SUCCEEDED(hr), "CreateSamplerState call failed in DX11ApiSamplerStateWrapper::DX11ApiSamplerStateWrapper");
	}

	DX11ApiSamplerStateWrapper::~DX11ApiSamplerStateWrapper()
	{
		if (m_poSamplerState)
		{
			m_poSamplerState->Release();
		}
	}
}