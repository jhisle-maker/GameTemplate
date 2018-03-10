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
#include "Color.h"
#include "Common.h"

namespace GT
{
	DX11GraphicDevice::DX11GraphicDevice(IUnknown* i_poCoreWindow, Viewport i_oScreenViewport)
		: m_poCoreWindow(i_poCoreWindow)
		, m_oScreenViewport(CD3D11_VIEWPORT(0.0f, 0.0f, i_oScreenViewport.m_fWidth, i_oScreenViewport.m_fHeight))
		, m_poDevice(nullptr)
		, m_poDeviceContext(nullptr)
		, m_poSwapChain(nullptr)
		, m_poD3DRenderTargetView(nullptr)
		, m_poD3DDepthStencilView(nullptr)
	{
		InitDeviceResources();
		InitWindowsSizeDependentResources();
	}

	DX11GraphicDevice::~DX11GraphicDevice()
	{
		//Nothing to do here
	}

	void DX11GraphicDevice::InitDeviceResources()
	{
		// This flag adds support for surfaces with a different color channel ordering
		// than the API default. It is required for compatibility with Direct2D.
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		HRESULT hr = D3D11CreateDevice
		(
			nullptr,
			D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
			0,
			D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
			nullptr,                    // Any feature level will do.
			0,
			D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
			nullptr,                    // No need to keep the D3D device reference.
			nullptr,                    // No need to know the feature level.
			nullptr                     // No need to keep the D3D device context reference.
		);

		if (hr == S_OK)
		{
			// If the project is in a debug build, enable debugging via SDK Layers with this flag.
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
		}
#endif

		// This array defines the set of DirectX hardware feature levels this app will support.
		// Note the ordering should be preserved.
		// Don't forget to declare your application's minimum required feature level in its
		// description.  All applications are assumed to support 9.1 unless otherwise stated.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		Microsoft::WRL::ComPtr<ID3D11Device> poDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> poDeviceContext;

		hr = D3D11CreateDevice
		(
			nullptr,					// Specify nullptr to use the default adapter.
			D3D_DRIVER_TYPE_HARDWARE,	// Create a device using the hardware graphics driver.
			0,							// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			creationFlags,				// Set debug and Direct2D compatibility flags.
			featureLevels,				// List of feature levels this app can support.
			ARRAYSIZE(featureLevels),	// Size of the list above.
			D3D11_SDK_VERSION,			// Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&poDevice,					// Returns the Direct3D device created.
			&m_oFeatureLevel,			// Returns feature level of device created.
			&poDeviceContext			// Returns the device immediate context.
		);

		GTASSERTL(hr == S_OK, "Creation of D3D11 Device and Context failed: falling back to WARP device");

		if (FAILED(hr))
		{
			// If the initialization fails, fall back to the WARP device.
			// For more information on WARP, see: 
			// http://go.microsoft.com/fwlink/?LinkId=286690
			hr = D3D11CreateDevice
			(
				nullptr,
				D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
				0,
				creationFlags,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&poDevice,
				&m_oFeatureLevel,
				&poDeviceContext
			);

			GTASSERTL(hr == S_OK, "Creation of D3D11 Warp Device and Context failed: falling back to WARP device");
		}

		poDevice.As(&m_poDevice);
		poDeviceContext.As(&m_poDeviceContext);
	}

	void DX11GraphicDevice::InitWindowsSizeDependentResources()
	{
		// Clear the previous window size specific context.
		ID3D11RenderTargetView* nullViews[] = { nullptr };
		m_poDeviceContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
		m_poD3DRenderTargetView = nullptr;
		m_poD3DDepthStencilView = nullptr;
		m_poDeviceContext->Flush1(D3D11_CONTEXT_TYPE_ALL, nullptr);

		if (m_poSwapChain != nullptr)
		{
			// If the swap chain already exists, resize it.
			HRESULT hr = m_poSwapChain->ResizeBuffers
			(
				2, // Double-buffered swap chain.
				lround(m_oScreenViewport.Width),
				lround(m_oScreenViewport.Height),
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0
			);

			if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
			{
				// If the device was removed for any reason, a new device and swap chain will need to be created.
				HandleDeviceLost();

				// Everything is set up now. Do not continue execution of this method. HandleDeviceLost will reenter this method 
				// and correctly set up the new device.
				return;
			}
			else
			{
				GTASSERTL(hr == S_OK, "Creation of SwapChain failed for some reason");
			}
		}
		else
		{
			// Otherwise, create a new one using the same adapter as the existing Direct3D device.
			DXGI_SCALING scaling = DXGI_SCALING_STRETCH;
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

			swapChainDesc.Width = lround(m_oScreenViewport.Width);		// Match the size of the window.
			swapChainDesc.Height = lround(m_oScreenViewport.Height);
			swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// This is the most common swap chain format.
			swapChainDesc.Stereo = false;
			swapChainDesc.SampleDesc.Count = 1;								// Don't use multi-sampling.
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 2;									// Use double-buffering to minimize latency.
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// All Windows Store apps must use this SwapEffect.
			swapChainDesc.Flags = 0;
			swapChainDesc.Scaling = scaling;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

			Microsoft::WRL::ComPtr<IDXGIDevice3> poDevice;
			m_poDevice.As(&poDevice);

			Microsoft::WRL::ComPtr<IDXGIAdapter> poDXGIAdapter;
			poDevice->GetAdapter(&poDXGIAdapter);

			Microsoft::WRL::ComPtr<IDXGIFactory4> poDXGIFactory;
			poDXGIAdapter->GetParent(IID_PPV_ARGS(&poDXGIFactory));

			Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
			HRESULT hr = poDXGIFactory->CreateSwapChainForCoreWindow
			(
				m_poDevice.Get(),
				m_poCoreWindow,
				&swapChainDesc,
				nullptr,
				&swapChain
			);

			GTASSERTL(hr == S_OK, "Creation of SwapChain failed!!");

			swapChain.As(&m_poSwapChain);

			// Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
			// ensures that the application will only render after each VSync, minimizing power consumption.
			poDevice->SetMaximumFrameLatency(1);
		}

		// Create a render target view of the swap chain back buffer.
		Microsoft::WRL::ComPtr<ID3D11Texture2D1> backBuffer;
		HRESULT hr = m_poSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		GTASSERTL(hr == S_OK, "Cannot retrieve backBuffer from swapChain");

		hr = m_poDevice->CreateRenderTargetView1(backBuffer.Get(), nullptr, &m_poD3DRenderTargetView);
		GTASSERTL(hr == S_OK, "Cannot create RenderTargetView form backBuffer");

		// Create a depth stencil view for use with 3D rendering if needed.
		CD3D11_TEXTURE2D_DESC1 depthStencilDesc
		(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			lround(m_oScreenViewport.Width),
			lround(m_oScreenViewport.Height),
			1, // This depth stencil view has only one texture.
			1, // Use a single mipmap level.
			D3D11_BIND_DEPTH_STENCIL
		);

		Microsoft::WRL::ComPtr<ID3D11Texture2D1> depthStencil;
		hr = m_poDevice->CreateTexture2D1(&depthStencilDesc, nullptr, &depthStencil);
		GTASSERTL(hr == S_OK, "Cannot create Texture2D for depthStencil buffer");

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		hr = m_poDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_poD3DDepthStencilView);

		// Set the 3D rendering viewport to target the entire window.
		m_poDeviceContext->RSSetViewports(1, &m_oScreenViewport);
	}

	void DX11GraphicDevice::HandleDeviceLost()
	{
		m_poSwapChain = nullptr;

		/*if (m_deviceNotify != nullptr)
		{
			m_deviceNotify->OnDeviceLost();
		}*/

		InitDeviceResources();
		InitWindowsSizeDependentResources();

		//if (m_deviceNotify != nullptr)
		//{
		//	m_deviceNotify->OnDeviceRestored();
		//}
	}

	void DX11GraphicDevice::OnScreenResolutionChanged(const size_t i_uiScreenHeight, const size_t i_uiScreenWidth)
	{
		m_oScreenViewport.Height = static_cast<float>(i_uiScreenHeight);
		m_oScreenViewport.Width = static_cast<float>(i_uiScreenWidth);

		if (m_oScreenViewport.Height == 0) m_oScreenViewport.Height = 1.0f;
		if (m_oScreenViewport.Width == 0) m_oScreenViewport.Width = 1.0f;

		InitWindowsSizeDependentResources();
	}

	void DX11GraphicDevice::OnSuspend()
	{
		Microsoft::WRL::ComPtr<IDXGIDevice3> poDxgiDevice;
		m_poDevice.As(&poDxgiDevice);

		poDxgiDevice->Trim();
	}

	void DX11GraphicDevice::Clear(Color color)
	{
		// Reset the viewport to target the whole screen.
		m_poDeviceContext->RSSetViewports(1, &m_oScreenViewport);

		// Reset render targets to the screen.
		ID3D11RenderTargetView *const targets[1] = { m_poD3DRenderTargetView.Get() };
		m_poDeviceContext->OMSetRenderTargets(1, targets, m_poD3DDepthStencilView.Get() );

		// Clear the back buffer and depth stencil view.
		m_poDeviceContext->ClearRenderTargetView(m_poD3DRenderTargetView.Get(), color.ToFloat4().data());
		m_poDeviceContext->ClearDepthStencilView(m_poD3DDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DX11GraphicDevice::Present()
	{
		// The first argument instructs DXGI to block until VSync, putting the application
		// to sleep until the next VSync. This ensures we don't waste any cycles rendering
		// frames that will never be displayed to the screen.
		DXGI_PRESENT_PARAMETERS parameters = { 0 };
		HRESULT hr = m_poSwapChain->Present1(1, 0, &parameters);

		// Discard the contents of the render target.
		// This is a valid operation only when the existing contents will be entirely
		// overwritten. If dirty or scroll rects are used, this call should be removed.
		m_poDeviceContext->DiscardView1(m_poD3DRenderTargetView.Get(), nullptr, 0);

		// Discard the contents of the depth stencil.
		m_poDeviceContext->DiscardView1(m_poD3DDepthStencilView.Get(), nullptr, 0);

		// If the device was removed either by a disconnection or a driver upgrade, we 
		// must recreate all device resources.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			HandleDeviceLost();
		}
		else
		{
			GTASSERTL(hr == S_OK, "Error while swapping backbuffers");
		}
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
		case 1u:
			eFormat = DXGI_FORMAT_R8_UINT;
			break;
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

	const Microsoft::WRL::ComPtr<ID3D11DeviceContext3> DX11GraphicDevice::GetDeviceContext() const
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

