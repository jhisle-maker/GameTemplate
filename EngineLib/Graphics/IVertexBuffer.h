#pragma once

namespace GT
{
	class IVertexBuffer
	{
	public:
		IVertexBuffer() {}
		virtual ~IVertexBuffer() {}

	public:
		virtual size_t GetVertexSize() const = 0;

		virtual void* GetInnerBuffer() const = 0;
		virtual void* const* GetInnerBufferAddress() const = 0;
	};
}