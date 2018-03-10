#pragma once
#include <wincodec.h>
#include "ITextureLoaderService.h"
#include <string>

namespace GT { class IGraphicContext; }
namespace GT { class IFileLoaderService; }

namespace GT
{
	class WicColorTexture2DLoaderService : public ITextureLoaderService
	{
	public:
		WicColorTexture2DLoaderService(const IFileLoaderService& i_oFileLoaderService, const IGraphicContext& i_oGraphicContext, const std::string& i_oBasePath);
		~WicColorTexture2DLoaderService();

	private:
		WicColorTexture2DLoaderService(const WicColorTexture2DLoaderService& i_oOther) = delete;
		WicColorTexture2DLoaderService& operator= (const WicColorTexture2DLoaderService& i_oOther) = delete;

	public:
		std::unique_ptr<ITexture> Load(const std::string& i_oTexturePath) const;

	private:
		IWICBitmapFrameDecode* GetFrame(uint8_t* textureData, const size_t textureDataSize) const;
		IWICBitmapSource* GetConvertedSource(IWICBitmapFrameDecode* i_poBitmapFrameDecode) const;

	private:
		const IFileLoaderService& m_oFileLoaderService;
		const IGraphicContext& m_oGraphicContext;
		const std::string m_oBasePath;

		IWICImagingFactory2* m_poImageFactory;
	};
}