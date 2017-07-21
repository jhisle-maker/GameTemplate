#include "WicTexture2DLoader.h"
#include "Graphics\Texture2D.h"
#include "Graphics\Color.h"
#include "Graphics\IGraphicContext.h"
#include "Loaders\IFileLoader.h"

namespace GT
{
	WicTexture2DLoader::WicTexture2DLoader(const IFileLoader& i_oFileLoader, const IGraphicContext& i_oGraphicContext)
		: m_oFileLoader(i_oFileLoader)
		, m_oGraphicContext(i_oGraphicContext)
		, m_poImageFactory(nullptr)
	{
		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_poImageFactory));
	}

	WicTexture2DLoader::~WicTexture2DLoader()
	{
		//Nothing to do here
	}

	std::unique_ptr<ITexture> WicTexture2DLoader::Load(const std::string& i_oTexturePath) const
	{
		std::vector<uint8_t> oTextureFileData;
		m_oFileLoader.Load(i_oTexturePath, oTextureFileData);

		if (oTextureFileData.size() > 0u)
		{
			IWICBitmapFrameDecode* poBitmapFrameDecode = GetFrame(oTextureFileData.data(), oTextureFileData.size());	
			IWICBitmapSource* poSource = GetConvertedSource(poBitmapFrameDecode);

			UINT width;
			UINT height;
			poSource->GetSize(&width, &height);

			std::vector<Color> sourceBuffer;
			sourceBuffer.resize(width * height);

			size_t colorSize = sizeof(Color);

			poSource->CopyPixels(nullptr, colorSize * width, width * height * colorSize, reinterpret_cast<BYTE*>(sourceBuffer.data()));

			return std::unique_ptr<ITexture>(new GT::Texture2D(sourceBuffer, width, height, m_oGraphicContext));
		}

		return nullptr;
	}

	IWICBitmapFrameDecode* WicTexture2DLoader::GetFrame(uint8_t* textureData, const size_t textureDataSize) const
	{
		IWICStream* poStream = nullptr;
		HRESULT result = m_poImageFactory->CreateStream(&poStream);
		if (result != S_OK || poStream == nullptr) return nullptr;

		result = poStream->InitializeFromMemory(textureData, textureDataSize);
		if (result != S_OK) return nullptr;

		IWICBitmapDecoder* poBpmDecoder = nullptr;
		result = m_poImageFactory->CreateDecoderFromStream(poStream, nullptr, WICDecodeOptions::WICDecodeMetadataCacheOnDemand, &poBpmDecoder);
		if (result != S_OK || poBpmDecoder == nullptr) return nullptr;

		IWICBitmapFrameDecode* poBitmapFrameDecode = nullptr;
		result = poBpmDecoder->GetFrame(0, &poBitmapFrameDecode);
		if (result != S_OK) return nullptr;

		return poBitmapFrameDecode;
	}

	IWICBitmapSource* WicTexture2DLoader::GetConvertedSource(IWICBitmapFrameDecode* i_poBitmapFrameDecode) const
	{
		IWICBitmapSource* poBmpSource = nullptr;

		WICPixelFormatGUID oPixelFormatGUID;
		HRESULT result = i_poBitmapFrameDecode->GetPixelFormat(&oPixelFormatGUID);
		if (result != S_OK) return nullptr;

		IWICFormatConverter* poFormatConverter = nullptr;
		if (oPixelFormatGUID != GUID_WICPixelFormat32bppRGBA)
		{
			result = m_poImageFactory->CreateFormatConverter(&poFormatConverter);
			if (result != S_OK) return nullptr;

			result = poFormatConverter->Initialize(i_poBitmapFrameDecode, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom);
			if (result != S_OK) return nullptr;

			poBmpSource = static_cast<IWICBitmapSource*>(poFormatConverter);
		}
		else
		{
			poBmpSource = static_cast<IWICBitmapSource*>(i_poBitmapFrameDecode);
		}

		return poBmpSource;
	}
}