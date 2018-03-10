#pragma once

#include "IFile.h"
#include <vector>
#include <stdint.h>

namespace GT
{
	class File : public IFile
	{
	public:
		File();
		~File();

	public:
		inline const std::vector<uint8_t>& GetData() const { return m_oData; }
		inline std::vector<uint8_t>& GetData() { return m_oData; }

	private:
		std::vector<uint8_t> m_oData;
	};
}
