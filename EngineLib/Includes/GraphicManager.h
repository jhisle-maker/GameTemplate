#pragma once

#include "IGraphicManager.h"
#include <memory>

namespace GT
{
	class GraphicManager : public IGraphicManager
	{
	public:
		GraphicManager(IGraphicDevice* i_poGraphicDevice, IGraphicContext* i_poGraphicContext);
		~GraphicManager();

	public:
		inline IGraphicDevice& GetGraphicDevice() { return *m_poGraphicDevice; }
		inline IGraphicContext& GetGraphicContext() { return *m_poGraphicContext; }
		inline IGraphicDevice& GetGraphicDevice() const { return *m_poGraphicDevice; }
		inline IGraphicContext& GetGraphicContext() const { return *m_poGraphicContext; }
		float GetScreenAspectRatio() const;

		void OnScreenResolutionChanged(const size_t i_uiHeight, const size_t i_uiWidth);
		void OnSuspend();

	private:
		GraphicManager(const GraphicManager& i_oOther) = delete;
		GraphicManager& operator=(const GraphicManager& i_oOther) = delete;

	private:
		std::unique_ptr<IGraphicDevice> m_poGraphicDevice;
		std::unique_ptr<IGraphicContext> m_poGraphicContext;
	};
}