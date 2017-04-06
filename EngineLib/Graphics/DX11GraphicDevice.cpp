#include "DX11GraphicDevice.h"

#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "IDX11ApiVertexBuffer.h"

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

		const IDX11ApiVertexBuffer* poApiBuffer = static_cast<const IDX11ApiVertexBuffer*>(i_oVertexBuffer.GetApiVertexBuffer());
		
		m_poDeviceContext->IASetVertexBuffers
		(
			0u,
			1u,
			poApiBuffer->GetD3D11BufferAddress(),
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

		m_poDeviceContext->IASetIndexBuffer
		(
			reinterpret_cast<ID3D11Buffer*>(i_oIndexBuffer.GetInnerBuffer()),
			eFormat,
			static_cast<UINT>(i_uiOffset)
		);
	}

	const Microsoft::WRL::ComPtr<ID3D11Device> DX11GraphicDevice::GetDevice() const
	{
		return m_poDevice;
	}

	const Microsoft::WRL::ComPtr<ID3D11DeviceContext> DX11GraphicDevice::GetDeviceContext() const
	{
		return m_poDeviceContext;
	}
}

