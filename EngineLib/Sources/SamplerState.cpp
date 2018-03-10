#include "SamplerState.h"

namespace GT
{
	SamplerState::SamplerState(const IGraphicContext& i_oGraphicContext)
		: m_poSamplerState(i_oGraphicContext.CreateApiSamplerState())
	{
		//Nothing to do here
	}

	SamplerState::~SamplerState()
	{
		//Nothing to do here
	}
}