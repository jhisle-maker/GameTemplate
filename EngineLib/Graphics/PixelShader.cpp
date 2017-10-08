#include "PixelShader.h"
#include "IGraphicContext.h"
#include "IConstBuffer.h"
#include "ITexture.h"
#include "ISamplerState.h"

namespace GT
{
	PixelShader::PixelShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext & i_oGraphicContext)
		: m_oGraphicContext(i_oGraphicContext)
		, m_poApiPixelShaderWrapper(i_oGraphicContext.CreateApiPixelShader(i_oShaderFileData))
	{
		//Nothing to do here
	}

	PixelShader::~PixelShader()
	{
		//Nothing to do here
	}

	void PixelShader::BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const
	{
		m_oGraphicContext.BindVertexShaderConstBuffer(i_oConstBuffer.GetApiWrapper());
	}

	void PixelShader::BindTexture(const ITexture& i_oTexture) const
	{
		m_oGraphicContext.BindPixelShaderTexture(i_oTexture.GetApiWrapper());
	}

	void PixelShader::BindSamplerState(const ISamplerState& i_oSamplerState) const
	{
		m_oGraphicContext.BindPixelShaderSampler(i_oSamplerState.GetApiWrapper());
	}
}
