#include "IGraphicDevice.h"
#include "DX11GraphicDevice.h"

namespace GT
{
	template<typename DataType>
	IndexBuffer<DataType>::IndexBuffer(const DataType* i_paoData, const size_t i_uiElementsCount, const IGraphicDevice& i_oGraphicContext)
	{
		CreateInnerBuffer(i_paoData, i_uiElementsCount, i_oGraphicContext);
	}

	template<typename DataType>
	IndexBuffer<DataType>::~IndexBuffer()
	{
		m_poInnerBuffer.Reset();
	}

	template<typename DataType>
	void IndexBuffer<DataType>::CreateInnerBuffer(const DataType* i_paoData, size_t i_uiElementsCount, const IGraphicDevice& i_oGraphicContext)
	{
		const DX11GraphicDevice& oDX11Context = static_cast<const DX11GraphicDevice&>(i_oGraphicContext);
		const Microsoft::WRL::ComPtr<ID3D11Device> pDevice = oDX11Context.GetDevice();

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = i_paoData;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(DataType) * i_uiElementsCount, D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed
		(
			pDevice->CreateBuffer
			(
				&indexBufferDesc,
				&indexBufferData,
				&m_poInnerBuffer
			)
		);
	}
}

