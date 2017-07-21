#pragma once

#include <memory>
#include <vector>

#include "ITexture.h"
#include "Color.h"
#include "IApiGraphicResourceWrapper.h"	

//START FORWARD DECL
namespace GT { class IGraphicContext; }
//END FORWARD DECL

namespace GT
{
	class Texture2D : public ITexture
	{
	public:
		Texture2D(const std::vector<Color>& i_aoData, const size_t i_uiWidth, const size_t i_uiHeight, const IGraphicContext& i_oGraphicContext);
		~Texture2D();

	public:
		size_t GetWidth() const {}
		size_t GetHeight() const {}
		const std::vector<Color>& GetData() const {}

	public:
		const IApiGraphicResourceWrapper& GetApiWrapper() const { return *m_poApiTexture2DWrapper; }
	
	private:
		const size_t m_uiWidth;
		const size_t m_uiHeight;
		std::unique_ptr<IApiGraphicResourceWrapper> m_poApiTexture2DWrapper;
	};
}