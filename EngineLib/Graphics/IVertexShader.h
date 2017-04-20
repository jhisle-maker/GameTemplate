#pragma once

//START FORWARD DECLS
namespace GT { class IApiVertexShaderWrapper; }
//END FORWARD DECLS

namespace GT
{
	class IVertexShader
	{
	public:
		IVertexShader() {}
		virtual ~IVertexShader() {}

	public:
		virtual const IApiVertexShaderWrapper& GetApiWrapper() const = 0;
	};
}