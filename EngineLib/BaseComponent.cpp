#include "BaseComponent.h"

#include "Services\IContext.h"

namespace GT
{
	BaseComponent::BaseComponent(const IContext& i_oContext)
		: m_oGraphicContext(i_oContext.GetGraphicContext())
		, m_oGraphicDevice(i_oContext.GetGraphicDevice())
		, m_oFileLoader(i_oContext.GetFileLoaderService())
		, m_oTextureLoader(i_oContext.GetTextureLoaderService())
		, m_oShaderManager(i_oContext.GetShaderManagerService())
	{
		//Nothing to do here
	}
}