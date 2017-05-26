#pragma once

#include "IIndexBuffer.h"
#include <memory>

//START FORWARD DECLS
namespace GT { class IGraphicContext; }
namespace GT { class IApiGraphicResource; }
//END FORWARD DECLS

namespace GT
{
	template<typename IndexType>
	class IndexBuffer : public IIndexBuffer
	{
	public:
		IndexBuffer(const IndexType* i_paoIndexData, const size_t i_uiIndexesCount, const IGraphicContext& i_oGraphicContext);
		virtual ~IndexBuffer();

	public:
		inline size_t GetIndexSize() const { return sizeof(IndexType); }
		virtual const IApiGraphicResource& GetApiWrapper() const { return *m_poApiIndexBufferWrapper; };

	private:
		std::unique_ptr<IApiGraphicResource> m_poApiIndexBufferWrapper;
	};
}

#include "IndexBuffer.inl"
