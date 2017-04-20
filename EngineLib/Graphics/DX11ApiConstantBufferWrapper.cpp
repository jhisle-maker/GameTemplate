#include "DX11ApiConstantBufferWrapper.h"

namespace GT
{
	DX11ApiConstantBufferWrapper::DX11ApiConstantBufferWrapper(ID3D11Buffer& i_oD3D11Buffer)
		: m_poBuffer(&i_oD3D11Buffer)
	{
		//Nothing to do here
	}

	DX11ApiConstantBufferWrapper::~DX11ApiConstantBufferWrapper()
	{
		if (m_poBuffer != nullptr)
		{
			m_poBuffer->Release();
		}
	}
}