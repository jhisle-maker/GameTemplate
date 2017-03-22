#include "IGraphicDevice.h"
#include "IGraphicContext.h"


namespace GT
{
	template<typename VertexType>
	VertexBuffer<VertexType>::VertexBuffer(const VertexType* i_paoVertexData, const size_t i_uiVertexCount, const IGraphicContext& i_oGraphicContext)
		: m_oGraphicContext(i_oGraphicContext)
	{
		m_oGraphicContext.CreateApiVertexBuffer(i_paoVertexData, sizeof(VertexType), i_uiVertexCount, m_poInnerBuffer);
	}

	template<typename VertexType>
	VertexBuffer<VertexType>::~VertexBuffer()
	{
		m_oGraphicContext.ReleaseApiVertexBuffer(m_poInnerBuffer);
	}
}

