#pragma once
#include <vector>
#include <memory>

#include "IPixelShader.h"
#include "IApiGraphicResource.h"

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
		inline const IApiGraphicResource& GetApiWrapper() const { return *m_poApiPixelShaderWrapper; }

	private:
		std::unique_ptr<IApiGraphicResource> m_poApiPixelShaderWrapper;
	};
}
