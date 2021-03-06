#pragma once

#include "Viewport.h"

//START FORWARD DECL
namespace GT { class IVertexShader; }
namespace GT { class IPixelShader; }
namespace GT { class IVertexBuffer; }
namespace GT { class IIndexBuffer; }
namespace GT { class Color; }
namespace GT { enum PrimitiveType; }
//END FORWARD DECL

namespace GT
{
	class IGraphicDevice
	{
	public:
		IGraphicDevice() {}
		virtual ~IGraphicDevice() {};

	public:
		virtual void Clear(Color color) = 0;
		virtual void Present() = 0;

		virtual void OnScreenResolutionChanged(const size_t i_uiScreenHeight, const size_t i_uiScreenWidth) = 0;
		virtual void OnSuspend() = 0;

		virtual void SetVertexBuffer(const IVertexBuffer& i_oVertexBuffer, const size_t i_uiOffset = 0u) const = 0;
		virtual void SetIndexBuffer(const IIndexBuffer& i_oIndexBuffer, const size_t i_uiOffset = 0u) const = 0;
		
		virtual void BindVertexShader(const IVertexShader& i_oVertexShader) const = 0;
		virtual void BindPixelShader(const IPixelShader& i_oPixelShader) const = 0;

		virtual void Draw(const PrimitiveType i_ePrimitiveType, const size_t i_uiVertexCount, const size_t i_uiVertexOffset = 0u) const = 0;
		virtual void DrawIndexed(const PrimitiveType i_ePrimitiveType, const size_t i_uiIndexCount, const size_t i_uiIndexOffset = 0u, const size_t i_uiVertexOffset = 0u) const = 0;

		virtual void EnableFaceCulling(const bool i_bEnabled) const = 0;
		virtual Viewport GetViewport() const = 0;
	};
}