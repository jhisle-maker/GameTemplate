#pragma once

//START FORWARD DECL
namespace GT { class IVertexBuffer; }
namespace GT { class IIndexBuffer; }
namespace GT { class IConstBuffer; }
namespace GT { class ITexture2D; }
namespace GT { class IVertexShader; }
namespace GT { class IPixelShader; }
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