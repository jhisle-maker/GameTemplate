#include "DX11BasicEffect.h"

#include<d3d11.h>
#include "Graphics\DX11GraphicDevice.h"

namespace GT
{
	DX11BasicEffect::DX11BasicEffect
	(
		Microsoft::WRL::ComPtr<ID3D11VertexShader> i_poVertexShader,
		Microsoft::WRL::ComPtr<ID3D11PixelShader> i_poPixelShader, 
		const DX11GraphicDevice& i_oGraphicDevice
	)
		: m_poVertexShader(i_poVertexShader)
		, m_poPixelShader(i_poPixelShader)
		, m_oGraphicDevice(i_oGraphicDevice)
	{
		InitConstantBuffer();
		//Nothing to do here
	}

	DX11BasicEffect::~DX11BasicEffect()
	{
		//Nothing to do here
	}

	void DX11BasicEffect::Apply(const Matrix& i_oModel, const Matrix& i_oView, const Matrix& i_oProjection)
	{

	}

	void DX11BasicEffect::InitConstantBuffer()
	{
		Microsoft::WRL::ComPtr<ID3D11Device> poDevice = m_oGraphicDevice.GetD3D11Device();

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ConstantBufferData), D3D11_BIND_CONSTANT_BUFFER);
		HRESULT result = poDevice->CreateBuffer(&constantBufferDesc, nullptr, &m_poConstBuffer);
		assert(result >= 0);
	}
}