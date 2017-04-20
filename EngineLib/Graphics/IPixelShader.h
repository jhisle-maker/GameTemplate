#pragma once

//START FORWARD DECL
namespace GT { class IApiPixelShaderWrapper; }
//END FORWARD DECL

namespace GT
{
	class IPixelShader
	{
	public:
		IPixelShader() {}
		virtual ~IPixelShader() {}

	public:
		virtual const IApiPixelShaderWrapper& GetApiWrapper() const = 0;
	};
}