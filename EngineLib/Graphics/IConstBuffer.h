#pragma once

//START FORWARD DECL
namespace GT { class IApiGraphicResource; }
//END FORWARD DECLS

namespace GT
{
	class IConstBuffer
	{
	public:
		IConstBuffer() {}
		virtual ~IConstBuffer() {}

	public:
		virtual const IApiGraphicResource& GetApiWrapper() const = 0;
	};
}
