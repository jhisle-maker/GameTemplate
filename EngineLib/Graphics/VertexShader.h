#pragma once
#include <vector>
#include <memory>

#include "IVertexShader.h"
#include "IApiGraphicResource.h"

//START FORWARD DECLARATION
namespace GT { class IGraphicContext; }
//END FORWARD DECLARATION

namespace GT
{
	template<typename VertexType>
	class VertexShader : public IVertexShader
	{
	public:
		VertexShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext& i_oGraphicContext);
		~VertexShader();

	public:
		inline const IApiGraphicResource& GetApiWrapper() const { return *m_poApiVertexShaderWrapper; }

	private:
		std::unique_ptr<IApiGraphicResource> m_poApiVertexShaderWrapper;
	};
}

#include "VertexShader.inl"
