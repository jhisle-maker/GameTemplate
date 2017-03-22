#include "DX11GraphicDevice.h"

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

	const Microsoft::WRL::ComPtr<ID3D11Device> DX11GraphicDevice::GetD3D11Device() const
	{
		return m_poDevice;
	}

	const Microsoft::WRL::ComPtr<ID3D11DeviceContext> DX11GraphicDevice::GetD3D11DeviceContext() const
	{
		return m_poDeviceContext;
	}
}

