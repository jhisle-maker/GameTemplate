#pragma once

namespace GT
{
	class IGraphicContext
	{
	public:
		virtual ~IGraphicContext() { }
		virtual void CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount, void*& o_oApiVertexBuffer) const = 0;
		virtual void CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount, void*& o_oApiIndexBuffer) const = 0;

		virtual void ReleaseApiVertexBuffer(void*& i_oApiVertexBuffer) const = 0;
		virtual void ReleaseApiIndexBuffer(void*& i_oApiIndexBuffer) const = 0;
	};
}

