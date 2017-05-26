#pragma once

//START FORWARD DECL
namespace GT { class IApiGraphicResource; }
//END FORWARD DECL

namespace GT
{
	class IPixelShader
	{
	public:
		IPixelShader() {}
		virtual ~IPixelShader() {}

	public:
		virtual const IApiGraphicResource& GetApiWrapper() const = 0;
	};
}