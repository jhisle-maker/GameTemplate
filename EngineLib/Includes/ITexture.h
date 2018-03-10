#pragma once

//START FORWARD DECL
namespace GT { class IApiGraphicResourceWrapper; }
//END FORWARD DECL

namespace GT
{
	class ITexture
	{
	public:
		ITexture() {}
		virtual ~ITexture() {}

	public:
		virtual const IApiGraphicResourceWrapper& GetApiWrapper() const = 0;

	private:
		ITexture(const ITexture& i_oOther) {};
		ITexture& operator=(const ITexture& i_oOther) {};
	};
}