#pragma once

//FORWARD DECLS
namespace GT
{
	class IGraphicDevice;
}

namespace GT
{
	template<typename DataType>
	class IndexBuffer
	{
	public:
		IndexBuffer(const DataType* i_paoData, const size_t i_uiElementsCount, const IGraphicDevice& i_oGraphicContext);
		virtual ~IndexBuffer();

	public:
		inline ID3D11Buffer* GetD3D11Buffer() const { return m_poInnerBuffer.Get(); }

	private:
		void CreateInnerBuffer(const DataType* i_paoData, const size_t i_uiElementsCount, const IGraphicDevice& i_oGraphicContext);

	private:
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_poInnerBuffer;

	private:
		size_t m_uiElementsCount;
	};
}

#include "IndexBuffer.inl"
