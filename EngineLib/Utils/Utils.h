#pragma once
#include <memory>
#include <fstream>
#include <vector>
#include <cstdint>
#include <wincodec.h>

namespace GT
{
	typedef unsigned char byte;

	class Utils
	{
	public:
		//static inline void LoadBmp(const std::string& i_oImagePath)
		//{
		//	std::vector<uint8_t> imgBuffer;
		//	ReadFileBytes(i_oImagePath, imgBuffer);

		//	IWICImagingFactory2* poImageFactory = nullptr;
		//	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&poImageFactory));

		//	IWICStream* poStream = nullptr;
		//	poImageFactory->CreateStream(&poStream);
		//	poStream->InitializeFromMemory(imgBuffer.data(), imgBuffer.size());

		//	IWICBitmapDecoder* poBpmDecoder = nullptr;
		//	poImageFactory->CreateDecoderFromStream(poStream, nullptr, WICDecodeOptions::WICDecodeMetadataCacheOnDemand, &poBpmDecoder);

		//	IWICBitmapFrameDecode* bmp = nullptr;
		//	poBpmDecoder->GetFrame(0, &bmp);


		//	UINT width;
		//	UINT height;
		//	bmp->GetSize(&width, &height);

		//	std::vector<uint8_t> sourceBuffer;
		//	sourceBuffer.resize(100);

		//	bmp->CopyPixels(nullptr, width, 100, sourceBuffer.data());
		//	//poImageFactory->CreateDecoder()
		//}
	};
}

