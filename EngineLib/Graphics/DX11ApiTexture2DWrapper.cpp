#include "DX11ApiTexture2DWrapper.h"

namespace GT
{
	DX11ApiTexture2DWrapper::DX11ApiTexture2DWrapper(ID3D11Device& i_oDevice, const void* i_paoData, const size_t i_uiWidth, const size_t i_uiHeight)
		: m_poTexture2D(nullptr)
		, m_poTexture2DSRV(nullptr)
	{
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.Width = static_cast<UINT>(i_uiWidth);
		desc.Height = static_cast<UINT>(i_uiHeight);
		desc.MipLevels = 1u;
		desc.ArraySize = 1u;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		D3D11_SUBRESOURCE_DATA dataDesc;
		memset(&dataDesc, 0, sizeof(dataDesc));
		dataDesc.pSysMem = i_paoData;
		dataDesc.SysMemPitch = 4u * static_cast<UINT>(i_uiWidth);
		dataDesc.SysMemSlicePitch = 0u;

		ID3D11ShaderResourceView* poSRV = nullptr;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvDesc.Texture2D.MipLevels = -1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		i_oDevice.CreateTexture2D(&desc, &dataDesc, &m_poTexture2D);
		i_oDevice.CreateShaderResourceView(m_poTexture2D, &srvDesc, &m_poTexture2DSRV);
		
	}

	DX11ApiTexture2DWrapper::~DX11ApiTexture2DWrapper()
	{
		if (m_poTexture2D != nullptr)
		{
			m_poTexture2D->Release();
		}
	}
}