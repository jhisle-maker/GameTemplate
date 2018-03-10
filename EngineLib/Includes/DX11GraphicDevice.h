#pragma once

#include <wrl/client.h>
#include <d3d11_3.h>
#include <dxgi1_4.h>
#include "IGraphicDevice.h"

namespace GT
{
	class DX11GraphicDevice : public IGraphicDevice
	{
	public:
		DX11GraphicDevice(IUnknown* i_poCoreWindow, Viewport i_oScreenViewport);
		~DX11GraphicDevice();

	public:
		void OnScreenResolutionChanged(const size_t i_uiScreenHeight, const size_t i_uiScreenWidth);
		void OnSuspend();

		void Clear(Color color);
		void Present();

		void SetVertexBuffer(const IVertexBuffer& i_oVertexBuffer, const size_t i_uiOffset = 0u) const;
		void SetIndexBuffer(const IIndexBuffer& i_oIndexBuffer, const size_t i_uiOffset = 0u) const;
	
		void BindVertexShader(const IVertexShader& i_oVertexShader) const;
		void BindPixelShader(const IPixelShader& i_oPixelShader) const;

		void Draw(const PrimitiveType i_ePrimitiveType, const size_t i_uiVertexCount, const size_t i_uiVertexOffset = 0u) const;
		void DrawIndexed(const PrimitiveType i_ePrimitiveType, const size_t i_uiIndexCount, const size_t i_uiIndexOffset = 0u, const size_t i_uiVertexOffset = 0u) const;

		void EnableFaceCulling(const bool i_bEnabled) const;

		const Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const;
		const Microsoft::WRL::ComPtr<ID3D11DeviceContext3> GetDeviceContext() const;

		inline Viewport GetViewport() const { return Viewport{ m_oScreenViewport.Width, m_oScreenViewport.Height }; }

	private:
		DX11GraphicDevice(const DX11GraphicDevice& i_oOther) = delete;
		DX11GraphicDevice& operator=(const DX11GraphicDevice& i_oOther) = delete;

		void InitDeviceResources();
		void InitWindowsSizeDependentResources();
		void HandleDeviceLost();

		void SetPrimitiveTopology(const PrimitiveType i_ePrimitiveType) const;

	private:
		IUnknown* m_poCoreWindow;
		Microsoft::WRL::ComPtr<ID3D11Device3> m_poDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext3> m_poDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain3>	m_poSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView1>	m_poD3DRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_poD3DDepthStencilView;
		D3D11_VIEWPORT									m_oScreenViewport;
		D3D_FEATURE_LEVEL m_oFeatureLevel;
	};
}