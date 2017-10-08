#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

//FORWARD DECLS
namespace GT { class IGraphicDevice; }
namespace GT { class IGraphicContext; }
namespace GT { class IFileLoaderService; }
namespace GT { class IShaderLoaderService; }
namespace GT { class ITextureLoaderService; }
namespace GT { class ILogger; }

// Renders Direct2D and 3D content on the screen.
namespace GameTemplate
{
	class GameTemplateMain : public DX::IDeviceNotify
	{
	public:
		GameTemplateMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~GameTemplateMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		//Graphics stuff
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<GT::IGraphicDevice> m_poGraphicDevice;
		std::unique_ptr<GT::IGraphicContext> m_poGraphicContext;
		
		//Services
		std::unique_ptr<GT::IFileLoaderService> m_poFileLoaderService;
		std::unique_ptr<GT::IShaderLoaderService> m_poShaderLoaderService;
		std::unique_ptr<GT::ITextureLoaderService> m_poTextureLoaderService;
		std::unique_ptr<GT::IServicesContext> m_poServicesContext;
		
		std::unique_ptr<GT::ILogger> m_poLogger;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<GT::Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}