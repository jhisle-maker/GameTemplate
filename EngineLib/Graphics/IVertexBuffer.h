#pragma once

//START FORWARD DECLS
namespace GT { class IApiBufferWrapper; }
//END FORWARD DECLS

namespace GT
{
	class IVertexBuffer
	{
	public:
		IVertexBuffer() {}
		virtual ~IVertexBuffer() {}

	public:
		virtual size_t GetVertexSize() const = 0;
		virtual const IApiBufferWrapper& GetApiBufferWrapper() const = 0;
	};
}