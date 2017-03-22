#pragma once

#include <wrl/client.h>
#include <d3d11_3.h>
#include "IGraphicDevice.h"

namespace GT
{
	class DX11GraphicDevice : public IGraphicDevice
	{
	public:
		DX11GraphicDevice
		(
			const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice, 
			const Microsoft::WRL::ComPtr<ID3D11DeviceContext> i_poDeviceContext
		);

		~DX11GraphicDevice();

	public:
		const Microsoft::WRL::ComPtr<ID3D11Device> GetD3D11Device() const;
		const Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetD3D11DeviceContext() const;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_poDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_poDeviceContext;
	};
}