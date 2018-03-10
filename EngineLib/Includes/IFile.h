#pragma once

#include <vector>
#include <stdint.h>

namespace GT
{
	class IFile
	{
	public:
		IFile() {}
		virtual ~IFile() {}

	public:
		virtual std::vector<uint8_t>& GetData() = 0;
		virtual const std::vector<uint8_t>& GetData() const = 0;
	};
}
