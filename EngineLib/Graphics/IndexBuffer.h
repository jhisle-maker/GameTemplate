#pragma once

//START FORWARD DECLS
namespace GT { class IGraphicContext; }
struct ID3D11Buffer;
//END FORWARD DECLS

namespace GT
{
	template<typename IndexType>
	class IndexBuffer
	{
	public:
		IndexBuffer(const IndexType* i_paoIndexData, const size_t i_uiIndexesCount, const IGraphicContext& i_oGraphicContext);
		virtual ~IndexBuffer();

	public:
		inline ID3D11Buffer* GetD3D11Buffer() const { return reinterpret_cast<ID3D11Buffer*>(m_poInnerBuffer); }

	private:
		const IGraphicContext& m_oGraphicContext;
		void* m_poInnerBuffer;
	};
}

#include "IndexBuffer.inl"
