#include "IGraphicContext.h"
#include "IApiGraphicResourceWrapper.h"

namespace GT
{
	template<typename DataType>
	ConstBuffer<DataType>::ConstBuffer(const DataType& i_oInitialData, const IGraphicContext& i_oGraphicContext)
		: m_poApiConstBufferWrapper(i_oGraphicContext.CreateApiConstantBuffer(&i_oInitialData, sizeof(DataType)))
		, m_oGraphicContext(i_oGraphicContext)
	{
		//Nothing to do here
	}

	template<typename DataType>
	ConstBuffer<DataType>::~ConstBuffer()
	{
		m_poApiConstBufferWrapper.release();
	}

	template<typename DataType>
	void ConstBuffer<DataType>::Update(const DataType& i_oData)
	{
		m_oGraphicContext.UpdateApiConstantBuffer(*m_poApiConstBufferWrapper, &i_oData);
	}
}

