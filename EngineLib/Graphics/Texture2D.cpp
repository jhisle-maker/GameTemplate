#include "Texture2D.h"
#include "IGraphicContext.h"

namespace GT
{
	Texture2D::Texture2D(const std::vector<Color>& i_aoData, const size_t i_uiWidth, const size_t i_uiHeight, const IGraphicContext& i_oGraphicContext)
		: m_uiWidth(i_uiWidth)
		, m_uiHeight(i_uiHeight)
		, m_poApiTexture2DWrapper(i_oGraphicContext.CreateApiTexture2D(i_aoData, i_uiWidth, i_uiHeight))
	{
		//Nothing to do here
	}

	Texture2D::~Texture2D()
	{
		//Nothing to do here
	}
}