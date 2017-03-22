#pragma once

//FORWARD DECLS
namespace GT
{
	class IGraphicDevice;
}

namespace GT
{
	template<typename VertexType>
	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexType* i_paoVertexData, const size_t i_uiVertexCount, const IGraphicDevice& i_oGraphicContext);
		virtual ~VertexBuffer();

	public:
		inline const ID3D11Buffer* GetD3D11Buffer() const { return m_poInnerBuffer.Get(); }
		inline ID3D11Buffer* const* GetD3D11BufferAddress() const { return m_poInnerBuffer.GetAddressOf(); }

	private:
		void CreateInnerBuffer(const VertexType* i_paoVertexData, size_t i_uiVertexCount, const IGraphicDevice& i_oGraphicContext);

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_poInnerBuffer;
	};
}

#include "VertexBuffer.inl"