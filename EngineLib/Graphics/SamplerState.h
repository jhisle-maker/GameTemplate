#pragma once
#include "ISamplerState.h"
#include "IGraphicContext.h"

namespace GT
{
	class SamplerState : public ISamplerState
	{
	public:
		SamplerState(const IGraphicContext& i_oGraphicContext);
		~SamplerState();

	public:
		inline const IApiGraphicResourceWrapper& GetApiWrapper() const { return *m_poSamplerState; }

	private:
		std::unique_ptr<IApiGraphicResourceWrapper> m_poSamplerState;
	};
}
