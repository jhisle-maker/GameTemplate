#pragma once
#include <wincodec.h>
#include "ITextureLoader.h"

namespace GT { class IGraphicContext; }
namespace GT { class IFileLoader; }

namespace GT
{
	class WicColorTexture2DLoader : ITextureLoader
	{
	public:
		WicColorTexture2DLoader(const IFileLoader& i_oFileLoader, const IGraphicContext& i_oGraphicContext);
		~WicColorTexture2DLoader();

	public:
		std::unique_ptr<ITexture> Load(const std::string& i_oTexturePath) const;

	private:
		IWICBitmapFrameDecode* GetFrame(uint8_t* textureData, const size_t textureDataSize) const;
		IWICBitmapSource* GetConvertedSource(IWICBitmapFrameDecode* i_poBitmapFrameDecode) const;

	private:
		const IFileLoader& m_oFileLoader;
		const IGraphicContext& m_oGraphicContext;
		IWICImagingFactory2* m_poImageFactory;
	};
}