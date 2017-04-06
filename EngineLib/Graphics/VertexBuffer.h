#pragma once

#include "IVertexBuffer.h"

//START FORWARD DECLS
namespace GT { class IGraphicContext; }
namespace GT { class IApiVertexBuffer; }
struct ID3D11Buffer;
//END FORWARD DECLS

namespace GT
{
	template<typename VertexType>
	class VertexBuffer : public IVertexBuffer
	{
	public:
		VertexBuffer(const VertexType* i_paoVertexData, const size_t i_uiVertexCount, const IGraphicContext& i_oGraphicContext);
		virtual ~VertexBuffer();

	public:
		inline size_t GetVertexSize() const { return sizeof(VertexType); }
		inline const IApiVertexBuffer* GetApiVertexBuffer() const { return m_poApiVertexBuffer; }

	public:
		inline const ID3D11Buffer* GetD3D11Buffer() const { return reinterpret_cast<ID3D11Buffer*>(m_poInnerBuffer); }
		inline ID3D11Buffer* const* GetD3D11BufferAddress() const { return reinterpret_cast<ID3D11Buffer* const*>(&m_poInnerBuffer); }

	private:
		const IGraphicContext& m_oGraphicContext;
		IApiVertexBuffer* m_poApiVertexBuffer;
	};
}

#include "VertexBuffer.inl"