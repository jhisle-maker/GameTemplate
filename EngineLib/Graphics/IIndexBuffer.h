#pragma once

//START FORWARD DECLS
namespace GT { class IApiGraphicResource; }
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
		virtual const IApiGraphicResource& GetApiWrapper() const = 0;
	};
}
