#include "IGraphicContext.h"

namespace GT
{
	template<typename IndexType>
	IndexBuffer<IndexType>::IndexBuffer(const IndexType* i_paoIndexData, const size_t i_uiIndexesCount, const IGraphicContext& i_oGraphicContext)
		: m_oGraphicContext(i_oGraphicContext)
	{
		m_oGraphicContext.CreateApiIndexBuffer(i_paoIndexData, sizeof(IndexType), i_uiIndexesCount, m_poInnerBuffer);
	}

	template<typename IndexType>
	IndexBuffer<IndexType>::~IndexBuffer()
	{
		m_oGraphicContext.ReleaseApiIndexBuffer(m_poInnerBuffer);
	}
}