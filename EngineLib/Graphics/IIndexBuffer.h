#pragma once

namespace GT
{
	class IIndexBuffer
	{
	public:
		IIndexBuffer() {}
		virtual ~IIndexBuffer() {}

	public:
		virtual size_t GetIndexSize() const = 0;
		virtual void* GetInnerBuffer() const = 0;
	};
}
