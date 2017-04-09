#pragma once

#include <memory>

//START FORWARD DECL
namespace GT { class IApiBufferWrapper; }
//END FORWARD DECL

namespace GT
{
	class IGraphicContext
	{
	public:
		virtual ~IGraphicContext() { }
		virtual std::unique_ptr<IApiBufferWrapper> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const = 0;
		virtual std::unique_ptr<IApiBufferWrapper> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const = 0;
		/*virtual void CreateApiVertexShader(const std::wstring& i_oShaderFileName, void*& o_oApiVertexShader) const = 0;
		virtual void CreateApiPixelShader(const std::wstring& i_oPixelShaderFileName, void*& o_oApiPixelShader) const = 0;*/

		virtual void ReleaseApiIndexBuffer(void*& i_oApiIndexBuffer) const = 0;
	};
}

