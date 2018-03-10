#include "IGraphicContext.h"

namespace GT
{
	template<typename IndexType>
	IndexBuffer<IndexType>::IndexBuffer(const IndexType* i_paoIndexData, const size_t i_uiIndexesCount, const IGraphicContext& i_oGraphicContext)
		: m_poApiIndexBufferWrapper(i_oGraphicContext.CreateApiIndexBuffer(i_paoIndexData, sizeof(IndexType), i_uiIndexesCount))
	{
		//Nothing to do here	 
	}

	template<typename IndexType>
	IndexBuffer<IndexType>::~IndexBuffer()
	{
		m_poApiIndexBufferWrapper.release();
	}
}