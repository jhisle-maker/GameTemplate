#pragma once
#include <vector>
#include <memory>

#include "IPixelShader.h"
#include "IApiGraphicResourceWrapper.h"

//START FORWARD DECLARATION
namespace GT { class IGraphicContext; }
namespace GT { class ITexture; }
//END FORWARD DECLARATION

namespace GT
{
	class PixelShader : public IPixelShader
	{
	public:
		PixelShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext& i_oGraphicContext);
		~PixelShader();

	public:
		void BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const;
		void BindTexture(const ITexture& i_oTexture) const;

		inline const IApiGraphicResourceWrapper& GetApiWrapper() const { return *m_poApiPixelShaderWrapper; }

	private:
		const IGraphicContext& m_oGraphicContext;
		std::unique_ptr<IApiGraphicResourceWrapper> m_poApiPixelShaderWrapper;
	};
}
