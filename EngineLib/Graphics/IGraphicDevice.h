#pragma once

//START FORWARD DECL
namespace GT { class IVertexShader; }
namespace GT { class IPixelShader; }
namespace GT { class IVertexBuffer; }
namespace GT { class IIndexBuffer; }
//END FORWARD DECL

namespace GT
{
	class IGraphicDevice
	{
	public:
		IGraphicDevice() {}
		virtual ~IGraphicDevice() {};

	public:
		virtual void SetVertexBuffer(const IVertexBuffer& i_oVertexBuffer, const size_t i_uiOffset = 0u) const = 0;
		virtual void SetIndexBuffer(const IIndexBuffer& i_oIndexBuffer, const size_t i_uiOffset = 0u) const = 0;
		
		virtual void BindVertexShader(const IVertexShader& i_oVertexShader) const = 0;
		virtual void BindPixelShader(const IPixelShader& i_oPixelShader) const = 0;
	};
}