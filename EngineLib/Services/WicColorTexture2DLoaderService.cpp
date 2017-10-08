#include "WicColorTexture2DLoaderService.h"
#include "Graphics\Color.h"
#include "Graphics\Texture2D.h"
#include "Graphics\IGraphicContext.h"
#include "Services\IFileLoaderService.h"
#include "Utils\Common.h"

namespace GT
{
	WicColorTexture2DLoaderService::WicColorTexture2DLoaderService(const IFileLoaderService& i_oFileLoaderService, const IGraphicContext& i_oGraphicContext)
		: m_oFileLoaderService(i_oFileLoaderService)
		, m_oGraphicContext(i_oGraphicContext)
		, m_poImageFactory(nullptr)
	{
		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_poImageFactory));
		GTASSERTL(SUCCEEDED(hr), "CoCreateInstance call failed in WicColorTexture2DLoader::WicColorTexture2DLoader");
	}

	WicColorTexture2DLoaderService::~WicColorTexture2DLoaderService()
	{
		//Nothing to do here
	}

	std::unique_ptr<ITexture> WicColorTexture2DLoaderService::Load(const std::string& i_oTexturePath) const
	{
		std::unique_ptr<ITexture> poTexture = nullptr;
		std::vector<uint8_t> oTextureFileData;
		m_oFileLoaderService.Load(i_oTexturePath, oTextureFileData);

		if (oTextureFileData.size() > 0u)
		{
			IWICBitmapFrameDecode* poBitmapFrameDecode = GetFrame(oTextureFileData.data(), oTextureFileData.size());
			GTASSERT(poBitmapFrameDecode);
			if (poBitmapFrameDecode)
			{
				IWICBitmapSource* poSource = GetConvertedSource(poBitmapFrameDecode);
				GTASSERT(poSource);
				if (poSource)
				{
					UINT width;
					UINT height;
					poSource->GetSize(&width, &height);

					std::vector<Color> sourceBuffer;
					sourceBuffer.resize(width * height);

					size_t colorSize = sizeof(Color);
					size_t stride = colorSize * width;
					size_t bufferSize = width * height * colorSize;

					poSource->CopyPixels(nullptr, (UINT)stride, (UINT)bufferSize, reinterpret_cast<BYTE*>(sourceBuffer.data()));
					poTexture = std::unique_ptr<ITexture>(new Texture2D<Color>(sourceBuffer, width, height, m_oGraphicContext));
				}
			}
		}

		GTASSERT(poTexture);
		return poTexture;
	}

	IWICBitmapFrameDecode* WicColorTexture2DLoaderService::GetFrame(uint8_t* textureData, const size_t textureDataSize) const
	{
		IWICStream* poStream = nullptr;
		IWICBitmapDecoder* poBpmDecoder = nullptr;
		IWICBitmapFrameDecode* poBitmapFrameDecode = nullptr;

		HRESULT result = m_poImageFactory->CreateStream(&poStream);
		GTASSERTL(SUCCEEDED(result) && poStream, "Error creating stream WicColorTexture2DLoader::GetFrame");
		
		if(poStream != nullptr && SUCCEEDED(result))
		{
			result = poStream->InitializeFromMemory(textureData, static_cast<DWORD>(textureDataSize));
			GTASSERTL(SUCCEEDED(result), "Error initializing stream in WicColorTexture2DLoader::GetFrame");

			if (SUCCEEDED(result))
			{
				result = m_poImageFactory->CreateDecoderFromStream(poStream, nullptr, WICDecodeOptions::WICDecodeMetadataCacheOnDemand, &poBpmDecoder);
				GTASSERTL(SUCCEEDED(result) && poBpmDecoder, "Error creating decoder in WicColorTexture2DLoader::GetFrame");

				if (poBpmDecoder != nullptr && SUCCEEDED(result))
				{
					result = poBpmDecoder->GetFrame(0, &poBitmapFrameDecode);
					GTASSERTL(SUCCEEDED(result) && poBitmapFrameDecode, "Error in getting frame in WicColorTexture2DLoader::GetFrame");
				}
			}
		}

		return poBitmapFrameDecode;
	}

	IWICBitmapSource* WicColorTexture2DLoaderService::GetConvertedSource(IWICBitmapFrameDecode* i_poBitmapFrameDecode) const
	{
		IWICBitmapSource* poBmpSource = nullptr;

		WICPixelFormatGUID oPixelFormatGUID;
		HRESULT result = i_poBitmapFrameDecode->GetPixelFormat(&oPixelFormatGUID);
		GTASSERTL(SUCCEEDED(result), "Error getting pixel format in WicColorTexture2DLoader::GetConvertedSource");
		
		if (SUCCEEDED(result) && oPixelFormatGUID != GUID_WICPixelFormat32bppRGBA)
		{
			IWICFormatConverter* poFormatConverter = nullptr;
			result = m_poImageFactory->CreateFormatConverter(&poFormatConverter);
			GTASSERTL(SUCCEEDED(result) && poFormatConverter != nullptr, "Error creating FormatConverter in WicColorTexture2DLoader::GetConvertedSource");

			if (SUCCEEDED(result) && poFormatConverter != nullptr)
			{
				result = poFormatConverter->Initialize(i_poBitmapFrameDecode, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom);
				GTASSERTL(SUCCEEDED(result), "Error initializing FormatConverter in WicColorTexture2DLoader::GetConvertedSource");

				if (SUCCEEDED(result))
				{
					poBmpSource = static_cast<IWICBitmapSource*>(poFormatConverter);
				}
			}
		}
		else
		{
			poBmpSource = static_cast<IWICBitmapSource*>(i_poBitmapFrameDecode);
		}
		
		return poBmpSource;
	}
}