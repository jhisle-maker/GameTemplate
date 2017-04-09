#pragma once

#include <ppltasks.h>
#include <wrl.h>
#include <wrl/client.h>
#include <dxgi1_4.h>
#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <concrt.h>
#include <fstream>

namespace GT
{
	inline void ReadFileBytes(const std::string& i_oFileName, std::vector<byte>& o_oBuffer)
	{
		o_oBuffer.clear();
		std::ifstream fileStream = std::ifstream();

		fileStream.open(i_oFileName.c_str(), std::ios::in | std::ios::binary);
		if (fileStream.is_open())
		{
			o_oBuffer.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
		}
		fileStream.close();
	}
}

