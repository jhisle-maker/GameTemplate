#include "pch.h"

#include "UWPManagersFactory.h"
#include "GraphicManager.h"
#include "InputManager.h"
#include "ContentManager.h"
#include "UWPKeyboardController.h"
#include "UWPFileLoaderService.h"
#include "ShaderLoaderService.h"
#include "WicColorTexture2DLoaderService.h"
#include "DX11GraphicContext.h"
#include "DX11GraphicDevice.h"

namespace GT
{
	UWPManagersFactory::UWPManagersFactory(Platform::Agile<Windows::UI::Core::CoreWindow> i_oWindow) : m_oAgileWindow(i_oWindow)
	{
		//Nothing to do here
	}

	UWPManagersFactory::~UWPManagersFactory()
	{
		//Nothing to do here
	}

	void UWPManagersFactory::CreateManagers
	(
		std::unique_ptr<IGraphicManager>& o_oGraphicManager,
		std::unique_ptr<IContentManager>& o_poContentManager,
		std::unique_ptr<IInputManager>& o_poInputManager
	) const
	{
		Viewport oScreenViewport { m_oAgileWindow.Get()->Bounds.Width, m_oAgileWindow.Get()->Bounds.Height };
		DX11GraphicDevice* poGraphicDevice = new DX11GraphicDevice(reinterpret_cast<IUnknown*>(m_oAgileWindow.Get()), oScreenViewport);
		DX11GraphicContext* poGraphicContext = new DX11GraphicContext(poGraphicDevice->GetDevice(), poGraphicDevice->GetDeviceContext());

		IFileLoaderService* poFileLoaderService = new UWPFileLoaderService();
		IShaderLoaderService* poShaderLoaderService = new ShaderLoaderService(*poFileLoaderService, *poGraphicContext);
		ITextureLoaderService* poTextureLoaderService = new WicColorTexture2DLoaderService(*poFileLoaderService, *poGraphicContext, "Content\\Textures\\");
		
		o_oGraphicManager = std::make_unique<GraphicManager>(poGraphicDevice, poGraphicContext);
		o_poContentManager = std::make_unique<ContentManager>(poFileLoaderService, poShaderLoaderService, poTextureLoaderService);
		o_poInputManager = std::make_unique<InputManager>(new UWPKeyboardController(m_oAgileWindow.Get()));
	}
}