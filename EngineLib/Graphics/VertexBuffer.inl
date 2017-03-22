#include "IGraphicDevice.h"
#include "DX11GraphicDevice.h"

namespace GT
{
	template<typename VertexType>
	VertexBuffer<VertexType>::VertexBuffer(const VertexType* i_paoVertexData, const size_t i_uiVertexCount, const IGraphicDevice& i_oGraphicContext)
	{
		CreateInnerBuffer(i_paoVertexData, i_uiVertexCount, i_oGraphicContext);
	}

	template<typename VertexType>
	VertexBuffer<VertexType>::~VertexBuffer()
	{
		m_poInnerBuffer.Reset();
	}

	template<typename VertexType>
	void VertexBuffer<VertexType>::CreateInnerBuffer(const VertexType* i_paoVertexData, size_t i_uiVertexCount, const IGraphicDevice& i_oGraphicContext)
	{
		const DX11GraphicDevice& oDX11Device = static_cast<const DX11GraphicDevice&>(i_oGraphicContext);
		const Microsoft::WRL::ComPtr<ID3D11Device>& poDevice = oDX11Device.GetDevice();

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = i_paoVertexData;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexType) * i_uiVertexCount, D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed
		(
			poDevice->CreateBuffer
			(
				&vertexBufferDesc,
				&vertexBufferData,
				&m_poInnerBuffer
			)
		);
	}
}

