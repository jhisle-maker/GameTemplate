#include "GraphicManager.h"

#include "IGraphicDevice.h"
#include "IGraphicContext.h"

namespace GT
{
	GraphicManager::GraphicManager(IGraphicDevice* i_poGraphicDevice, IGraphicContext* i_poGraphicContext)
		: m_poGraphicDevice(i_poGraphicDevice)
		, m_poGraphicContext(i_poGraphicContext)
	{
		//Nothing to do here
	}
	
	GraphicManager::~GraphicManager()
	{
		//Nothing to do here
	}

	void GraphicManager::OnScreenResolutionChanged(const size_t i_uiWidth, const size_t i_uiHeight)
	{
		m_poGraphicDevice->OnScreenResolutionChanged(i_uiHeight, i_uiWidth);
	}

	void GraphicManager::OnSuspend()
	{
		m_poGraphicDevice->OnSuspend();
	}

	float GraphicManager::GetScreenAspectRatio() const
	{
		Viewport oViewPort = m_poGraphicDevice->GetViewport();
		float aspectRatio = oViewPort.m_fWidth / oViewPort.m_fHeight; 

		return aspectRatio;
	}
}