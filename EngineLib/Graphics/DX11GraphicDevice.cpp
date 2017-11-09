#include "DX11GraphicDevice.h"

#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "IConstBuffer.h"
#include "IVertexShader.h"
#include "IPixelShader.h"
#include "DX11ApiVertexBufferWrapper.h"
#include "DX11ApiIndexBufferWrapper.h"
#include "DX11ApiConstantBufferWrapper.h"
#include "DX11ApiVertexShaderWrapper.h"
#include "DX11ApiPixelShaderWrapper.h"
#include "PrimitiveType.h"
#include "Utils\Common.h"

namespace GT
{
	DX11GraphicDevice::DX11GraphicDevice(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice, const Microsoft::WRL::ComPtr<ID3D11DeviceContext> i_poDeviceContext)
		: m_poDevice(i_poDevice)
		, m_poDeviceContext(i_poDeviceContext)
	{
		//Nothing to do here
	}

	DX11GraphicDevice::~DX11GraphicDevice()
	{
		//Nothing to do here
	}

	void DX11GraphicDevice::SetVertexBuffer(const IVertexBuffer& i_oVertexBuffer, const size_t i_uiOffset) const
	{
		UINT stride = static_cast<UINT>(i_oVertexBuffer.GetVertexSize());
		UINT offset = 0;

		const DX11ApiVertexBufferWrapper& poApiBuffer = static_cast<const DX11ApiVertexBufferWrapper&>(i_oVertexBuffer.GetApiWrapper());

		m_poDeviceContext->IASetVertexBuffers
		(
			0u,
			1u,
			poApiBuffer.GetD3D11BufferPtrAddress(),
			&stride,
			reinterpret_cast<const UINT*>(&i_uiOffset)
		);
	}

	void DX11GraphicDevice::SetIndexBuffer(const IIndexBuffer& i_oIndexBuffer, const size_t i_uiOffset) const
	{
		DXGI_FORMAT eFormat;
		switch (i_oIndexBuffer.GetIndexSize())
		{
		case 2u:
			eFormat = DXGI_FORMAT_R16_UINT;
			break;
		case 4u:
			eFormat = DXGI_FORMAT_R32_UINT;
			break;
		}

		const DX11ApiIndexBufferWrapper& poApiBuffer = static_cast<const DX11ApiIndexBufferWrapper&>(i_oIndexBuffer.GetApiWrapper());

		m_poDeviceContext->IASetIndexBuffer
		(
			poApiBuffer.GetD3D11BufferPtr(),
			eFormat,
			static_cast<UINT>(i_uiOffset)
		);
	}

	void DX11GraphicDevice::BindVertexShader(const IVertexShader& i_oVertexShader) const
	{
		const DX11ApiVertexShaderWrapper& oApiShader = static_cast<const DX11ApiVertexShaderWrapper&>(i_oVertexShader.GetApiWrapper());

		m_poDeviceContext->IASetInputLayout(oApiShader.GetDX11InputLayout());
		m_poDeviceContext->VSSetShader(oApiShader.GetDX11VertexShader(), nullptr, 0);
	}

	void DX11GraphicDevice::BindPixelShader(const IPixelShader& i_oPixelShader) const
	{
		const DX11ApiPixelShaderWrapper& oApiShader = static_cast<const DX11ApiPixelShaderWrapper&>(i_oPixelShader.GetApiWrapper());
		m_poDeviceContext->PSSetShader(oApiShader.GetDX11PixelShader(), nullptr, 0);
	}

	void DX11GraphicDevice::Draw(PrimitiveType i_ePrimitiveType, size_t i_uiVertexCount, size_t i_uiVertexOffset) const
	{
		SetPrimitiveTopology(i_ePrimitiveType);
		m_poDeviceContext->Draw(static_cast<UINT>(i_uiVertexCount), static_cast<INT>(i_uiVertexOffset));
	}

	void DX11GraphicDevice::DrawIndexed(PrimitiveType i_ePrimitiveType, size_t i_uiIndexCount, size_t i_uiIndexOffset, size_t i_uiVertexOffset) const
	{
		SetPrimitiveTopology(i_ePrimitiveType);
		m_poDeviceContext->DrawIndexed(static_cast<UINT>(i_uiIndexCount), static_cast<UINT>(i_uiIndexOffset), static_cast<INT>(i_uiVertexOffset));
	}

	void DX11GraphicDevice::EnableFaceCulling(const bool m_bEnabled) const
	{
		/*ID3D11RasterizerState* rsState = nullptr;
		m_poDeviceContext->RSGetState(&rsState);

		D3D11_RASTERIZER_DESC rsDesc;
		memset(&rsDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

		rsState->GetDesc(&rsDesc);

		if (!m_bEnabled && rsDesc.CullMode != D3D11_CULL_NONE)
		{
			rsDesc.CullMode = D3D11_CULL_NONE;
			m_poDevice->CreateRasterizerState(&rsDesc, &rsState);
			m_poDeviceContext->RSSetState(rsState);
		}
		
		if(m_bEnabled && rsDesc.CullMode == D3D11_CULL_NONE)
		{
			rsDesc.CullMode = D3D11_CULL_BACK;
			m_poDevice->CreateRasterizerState(&rsDesc, &rsState);
			m_poDeviceContext->RSSetState(rsState);
		}*/
	}
	
	const Microsoft::WRL::ComPtr<ID3D11Device> DX11GraphicDevice::GetDevice() const
	{
		return m_poDevice;
	}

	const Microsoft::WRL::ComPtr<ID3D11DeviceContext> DX11GraphicDevice::GetDeviceContext() const
	{
		return m_poDeviceContext;
	}

	void DX11GraphicDevice::SetPrimitiveTopology(const PrimitiveType i_ePrimitiveType) const
	{
		switch (i_ePrimitiveType)
		{
		case PrimitiveType::eTRIANGLE_LIST:
			m_poDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;
		case PrimitiveType::eTRIANGLE_STRIP:
			m_poDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			break;
		case PrimitiveType::eLINE_LIST:
			m_poDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			break;
		default:
			GTASSERTL(false, "PrimitiveType not supported while calling draw");
		}
	}
}

