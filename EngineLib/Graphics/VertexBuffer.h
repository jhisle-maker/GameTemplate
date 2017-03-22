#pragma once

//FORWARD DECLS
namespace GT { class IGraphicContext; }
struct ID3D11Buffer;

namespace GT
{
	template<typename VertexType>
	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexType* i_paoVertexData, const size_t i_uiVertexCount, const IGraphicContext& i_oGraphicContext);
		virtual ~VertexBuffer();

	public:
		inline const ID3D11Buffer* GetD3D11Buffer() const { return reinterpret_cast<ID3D11Buffer*>(m_poInnerBuffer); }
		inline ID3D11Buffer* const* GetD3D11BufferAddress() const { return reinterpret_cast<ID3D11Buffer* const*>(&m_poInnerBuffer); }

	private:
		const IGraphicContext& m_oGraphicContext;
		void* m_poInnerBuffer;
	};
}

#include "VertexBuffer.inl"