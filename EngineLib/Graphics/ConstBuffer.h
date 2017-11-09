#pragma once

#include <memory>
#include "IConstBuffer.h"

//START FORWARD DECLS
namespace GT { class IGraphicContext; }
namespace GT { class IApiGraphicResourceWrapper; }
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
		inline const IApiGraphicResourceWrapper& GetApiWrapper() const { return *m_poApiConstBufferWrapper; }

	private:
		ConstBuffer(const ConstBuffer&  i_oOther) = delete;
		ConstBuffer& operator=(const ConstBuffer& i_oOther) = delete;

	private:
		std::unique_ptr<IApiGraphicResourceWrapper> m_poApiConstBufferWrapper;
		const IGraphicContext& m_oGraphicContext;
	};
}

#include "ConstBuffer.inl"