#pragma once

#include <memory>
#include "IVertexBuffer.h"


//START FORWARD DECLS
namespace GT { class IGraphicContext; }
namespace GT { class IApiBufferWrapper; }
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
		inline const IApiBufferWrapper& GetApiBufferWrapper() const { return *m_poApiVertexBufferWrapper; }

	private:
		std::unique_ptr<IApiBufferWrapper> m_poApiVertexBufferWrapper;
	};
}

#include "VertexBuffer.inl"