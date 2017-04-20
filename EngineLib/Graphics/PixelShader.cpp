#include "PixelShader.h"
#include "IGraphicContext.h"

GT::PixelShader::PixelShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext & i_oGraphicContext)
	: m_poApiPixelShaderWrapper(i_oGraphicContext.CreateApiPixelShader(i_oShaderFileData))
{
	//Nothing to do here
}

GT::PixelShader::~PixelShader()
{
	//Nothing to do here
}
