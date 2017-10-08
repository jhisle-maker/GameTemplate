#include "pch.h"
#include "GameTemplateMain.h"
#include "Common\DirectXHelper.h"

#include "Services\ServicesContext.h"
#include "Services\UWPFileLoaderService.h"
#include "Services\ShaderLoaderService.h"
#include "Services\WicColorTexture2DLoaderService.h"

#include "Graphics\DX11GraphicDevice.h"
#include "Graphics\DX11GraphicContext.h"

#include "Logger\Logger.h"
#include "Logger\VSLogger.h"


using namespace GameTemplate;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// Loads and initializes application assets when the application is loaded.
GameTemplateMain::GameTemplateMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources)
{
	m_poLogger = std::unique_ptr<GT::ILogger>(new GT::VSLogger());

	GT::Logger::Init(*m_poLogger);
	GT::Logger::Log("***** LOG STARTED *****");

	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	//Graphic stuff
	m_poGraphicDevice = std::make_unique<GT::DX11GraphicDevice>(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());
	m_poGraphicContext = std::make_unique<GT::DX11GraphicContext>(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());
	
	//Services
	m_poFileLoaderService = std::make_unique<GT::UWPFileLoaderService>();
	m_poShaderLoaderService = std::make_unique<GT::ShaderLoaderService>(*m_poFileLoaderService, *m_poGraphicContext);
	m_poTextureLoaderService = std::make_unique<GT::WicColorTexture2DLoaderService>(*m_poFileLoaderService, *m_poGraphicContext);
	
	m_poServicesContext = std::make_unique<GT::ServicesContext>
	(
		*m_poFileLoaderService,
		*m_poShaderLoaderService,
		*m_poTextureLoaderService
	);

	//Renderers
	m_sceneRenderer = std::make_unique<GT::Sample3DSceneRenderer>(m_deviceResources, *m_poGraphicDevice, *m_poGraphicContext, *m_poServicesContext);
	m_fpsTextRenderer = std::make_unique<SampleFpsTextRenderer>(m_deviceResources);

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

GameTemplateMain::~GameTemplateMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void GameTemplateMain::CreateWindowSizeDependentResources() 
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

// Updates the application state once per frame.
void GameTemplateMain::Update() 
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		// TODO: Replace this with your app's content update functions.
		m_sceneRenderer->Update(m_timer);
		m_fpsTextRenderer->Update(m_timer);
	});
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool GameTemplateMain::Render() 
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// Clear the back buffer and depth stencil view.
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_sceneRenderer->Render();
	m_fpsTextRenderer->Render();

	return true;
}

// Notifies renderers that device resources need to be released.
void GameTemplateMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void GameTemplateMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	m_fpsTextRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
