#pragma once

//START FORWARD DECL
namespace GT { class IApiGraphicResourceWrapper; }
namespace GT { class IConstBuffer; }
namespace GT { class ITexture; }
namespace GT { class ISamplerState; }
//END FORWARD DECL

namespace GT
{
	class IPixelShader
	{
	public:
		IPixelShader() {}
		virtual ~IPixelShader() {}

	public:
		virtual void BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const = 0;
		virtual void BindTexture(const ITexture& i_oTexture) const = 0;
		virtual void BindSamplerState(const ISamplerState& i_oSamplerState) const = 0;

		virtual const IApiGraphicResourceWrapper& GetApiWrapper() const = 0;

	private:
		IPixelShader(const IPixelShader& i_oOther) {};
		IPixelShader& operator=(const IPixelShader& i_oOther) {};
	};
}