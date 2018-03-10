#pragma once

//START FORWARD DECLS
namespace GT { class IApiGraphicResourceWrapper; }
//END FORWARD DECLS

namespace GT
{
	class IIndexBuffer
	{
	public:
		IIndexBuffer() {}
		virtual ~IIndexBuffer() {}

	public:
		virtual size_t GetIndexSize() const = 0;
		virtual const IApiGraphicResourceWrapper& GetApiWrapper() const = 0;
	};
}
