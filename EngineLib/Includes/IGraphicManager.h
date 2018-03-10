#pragma once

//START FORWARD DECL
namespace GT { class IGraphicDevice; }
namespace GT { class IGraphicContext; }
//END FORWARD DECL

namespace GT
{
	class IGraphicManager
	{
	public:
		IGraphicManager() {}
		virtual ~IGraphicManager() {}

	public:
		virtual IGraphicDevice& GetGraphicDevice() const = 0;
		virtual IGraphicContext& GetGraphicContext() const = 0;		
		virtual float GetScreenAspectRatio() const = 0;

		virtual void OnScreenResolutionChanged(const size_t i_uiWidth, const size_t i_uiHeight) = 0;
		virtual void OnSuspend() = 0;
	};
}