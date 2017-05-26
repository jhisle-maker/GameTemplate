#pragma once

#include "IConstBuffer.h"

//START FORWARD DECLS
namespace GT { class IGraphicContext; }
namespace GT { class IApiGraphicResource; }
//END FORWARD DECLS

namespace GT
{
	template<typename DataType>
	class ConstBuffer : public IConstBuffer
	{
	public:
		ConstBuffer(const DataType& i_oInitialData, const IGraphicContext& i_oGraphicContext);
		virtual ~ConstBuffer();

	public:
		void Update(const DataType& i_oData);
		inline const IApiGraphicResource& GetApiWrapper() const { return *m_poApiConstBufferWrapper; }

	private:
		std::unique_ptr<IApiGraphicResource> m_poApiConstBufferWrapper;
		const IGraphicContext& m_oGraphicContext;
	};
}

#include "ConstBuffer.inl"