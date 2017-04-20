#pragma once
#include <vector>
#include <memory>

#include "IPixelShader.h"
#include "IApiPixelShaderWrapper.h"

//START FORWARD DECLARATION
namespace GT { class IGraphicContext; }
//END FORWARD DECLARATION

namespace GT
{
	class PixelShader : public IPixelShader
	{
	public:
		PixelShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext& i_oGraphicContext);
		~PixelShader();

	public:
		inline const IApiPixelShaderWrapper& GetApiWrapper() const { return *m_poApiPixelShaderWrapper; }

	private:
		std::unique_ptr<IApiPixelShaderWrapper> m_poApiPixelShaderWrapper;
	};
}
