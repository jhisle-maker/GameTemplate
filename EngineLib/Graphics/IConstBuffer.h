#pragma once

//START FORWARD DECL
namespace GT { class IApiBufferWrapper; }
//END FORWARD DECLS

namespace GT
{
	class IConstBuffer
	{
	public:
		IConstBuffer() {}
		virtual ~IConstBuffer() {}

	public:
		virtual const IApiBufferWrapper& GetApiWrapper() const = 0;
	};
}
