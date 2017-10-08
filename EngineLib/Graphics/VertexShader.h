#pragma once
#include <vector>
#include <memory>

#include "IVertexShader.h"
#include "IApiGraphicResourceWrapper.h"

//START FORWARD DECLARATION
namespace GT { class IGraphicContext; }
namespace GT { struct VertexDeclaration; }
//END FORWARD DECLARATION

namespace GT
{
	class VertexShader : public IVertexShader
	{
	public:
		VertexShader(const std::vector<uint8_t>& i_oShaderFileData, const VertexDeclaration& i_oVertexDeclaration, const IGraphicContext& i_oGraphicContext);
		~VertexShader();

		void BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const;
		void BindTexture(const ITexture& i_oTexture) const;

	public:
		inline const IApiGraphicResourceWrapper& GetApiWrapper() const { return *m_poApiVertexShaderWrapper; }

	private:
		VertexShader(const VertexShader& i_oVertexShader) = delete;
		VertexShader& operator=(const VertexShader& i_oVertexShader) = delete;

	private:
		const IGraphicContext& m_oGraphicContext;
		std::unique_ptr<IApiGraphicResourceWrapper> m_poApiVertexShaderWrapper;
	};
}
