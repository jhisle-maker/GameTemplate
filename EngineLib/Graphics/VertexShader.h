#pragma once
#include <vector>
#include <memory>

#include "IVertexShader.h"
#include "IApiGraphicResourceWrapper.h"

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

		void BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const;
		void BindTexture(const ITexture& i_oTexture) const;

	public:
		inline const IApiGraphicResourceWrapper& GetApiWrapper() const { return *m_poApiVertexShaderWrapper; }

	private:
		const IGraphicContext& m_oGraphicContext;
		std::unique_ptr<IApiGraphicResourceWrapper> m_poApiVertexShaderWrapper;
	};
}

#include "VertexShader.inl"
