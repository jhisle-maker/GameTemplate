#pragma once

//START FORWARD DECLS
namespace GT { class IApiGraphicResourceWrapper; }
namespace GT { class IConstBuffer; }
namespace GT { class ITexture; }
//END FORWARD DECLS

namespace GT
{
	class IVertexShader
	{
	public:
		IVertexShader() {}
		virtual ~IVertexShader() {}

	public:
		virtual void BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const = 0;
		virtual void BindTexture(const ITexture& i_oTexture) const = 0;
		virtual const IApiGraphicResourceWrapper& GetApiWrapper() const = 0;
	};
}