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
	};
}