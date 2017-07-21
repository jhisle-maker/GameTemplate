#pragma once

//START FORWARD DECL
namespace GT { class IApiGraphicResourceWrapper; }
//END FORWARD DECLS

namespace GT
{
	class IConstBuffer
	{
	public:
		IConstBuffer() {}
		virtual ~IConstBuffer() {}

	public:
		virtual const IApiGraphicResourceWrapper& GetApiWrapper() const = 0;
	};
}
