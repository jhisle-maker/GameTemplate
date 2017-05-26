#pragma once

//START FORWARD DECLS
namespace GT { class IApiGraphicResource; }
namespace GT { class IConstBuffer; }
//END FORWARD DECLS

namespace GT
{
	class IVertexShader
	{
	public:
		IVertexShader() {}
		virtual ~IVertexShader() {}

	public:
		virtual const IApiGraphicResource& GetApiWrapper() const = 0;
	};
}