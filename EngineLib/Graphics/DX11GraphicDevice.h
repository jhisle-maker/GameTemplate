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
		void SetVertexBuffer(const IVertexBuffer& i_oVertexBuffer, const size_t i_uiOffset = 0u) const;
		void SetIndexBuffer(const IIndexBuffer& i_oIndexBuffer, const size_t i_uiOffset = 0u) const;
	
		void BindVertexShader(const IVertexShader& i_oVertexShader) const;
		void BindPixelShader(const IPixelShader& i_oPixelShader) const;

		void Draw(const PrimitiveType i_ePrimitiveType, const size_t i_uiVertexCount, const size_t i_uiVertexOffset = 0u) const;
		void DrawIndexed(const PrimitiveType i_ePrimitiveType, const size_t i_uiIndexCount, const size_t i_uiIndexOffset = 0u, const size_t i_uiVertexOffset = 0u) const;

		void EnableFaceCulling(const bool i_bEnabled) const;

		const Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const;
		const Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() const;

	private:
		DX11GraphicDevice(const DX11GraphicDevice& i_oOther) = delete;
		DX11GraphicDevice& operator=(const DX11GraphicDevice& i_oOther) = delete;

		void SetPrimitiveTopology(const PrimitiveType i_ePrimitiveType) const;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_poDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_poDeviceContext;
	};
}