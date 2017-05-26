#include "IGraphicContext.h"
#include "IApiGraphicResource.h"

namespace GT
{
	template<typename VertexType>
	VertexBuffer<VertexType>::VertexBuffer(const VertexType* i_paoVertexData, const size_t i_uiVertexCount, const IGraphicContext& i_oGraphicContext)
		: m_poApiVertexBufferWrapper(i_oGraphicContext.CreateApiVertexBuffer(i_paoVertexData, sizeof(VertexType), i_uiVertexCount))
	{
		//Nothing to do here
	}

	template<typename VertexType>
	VertexBuffer<VertexType>::~VertexBuffer()
	{
		m_poApiVertexBufferWrapper.release();
	}
}

