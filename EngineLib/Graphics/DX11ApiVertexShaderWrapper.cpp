#include "DX11ApiVertexShaderWrapper.h"

GT::DX11ApiVertexShaderWrapper::DX11ApiVertexShaderWrapper(ID3D11VertexShader& i_oVertexShader, ID3D11InputLayout& i_oInputLayout)
	: m_poVertexShader(&i_oVertexShader)
	, m_poInputLayout(&i_oInputLayout)
{
	//Nothing to do here
}

GT::DX11ApiVertexShaderWrapper::~DX11ApiVertexShaderWrapper()
{
	if (m_poVertexShader != nullptr)
	{
		m_poVertexShader->Release();
	}

	if (m_poInputLayout != nullptr)
	{
		m_poInputLayout->Release();
	}
}
