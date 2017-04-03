#pragma once

#include "IIndexBuffer.h"

//START FORWARD DECLS
namespace GT { class IGraphicContext; }
struct ID3D11Buffer;
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
		inline void* GetInnerBuffer() const { return m_poInnerBuffer; }

	private:
		const IGraphicContext& m_oGraphicContext;
		void* m_poInnerBuffer;
	};
}

#include "IndexBuffer.inl"
