#include "DX11ApiVertexShaderWrapper.h"
#include "VertexDeclaration.h"

GT::DX11ApiVertexShaderWrapper::DX11ApiVertexShaderWrapper(ID3D11Device& i_oDevice, const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration)
	: m_poVertexShader(nullptr)
	, m_poInputLayout(nullptr)
{
	i_oDevice.CreateVertexShader
	(
		i_oShaderFileBytes.data(),
		i_oShaderFileBytes.size(),
		nullptr,
		reinterpret_cast<ID3D11VertexShader**>(&m_poVertexShader)
	);

	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexDescArray;
	vertexDescArray.reserve(vertexDeclaration.VertexDeclarationItemsCount);

	UINT alignedByteOffset = 0;
	for (int index = 0; index < vertexDeclaration.VertexDeclarationItemsCount; ++index)
	{
		char* semanticName = nullptr;
		DXGI_FORMAT format;
		UINT formatByteSize = 0;

		VertexDeclarationItem vertexDeclarationItem = vertexDeclaration.VertexDeclarationItems[index];
		switch (vertexDeclarationItem.Type)
		{
		case FLOAT32:
			format = DXGI_FORMAT_R32G32B32_FLOAT;
			formatByteSize = 12;
			break;
		}

		switch (vertexDeclarationItem.Usage)
		{
		case POSITION:
			semanticName = "POSITION";
			break;
		case COLOR:
			semanticName = "COLOR";
			break;
		case TEXTURE:
			semanticName = "TEXTURE";
			break;
		case NORMAL:
			semanticName = "NORMAL";
			break;
		}

		vertexDescArray.push_back({ semanticName, 0, format, 0, alignedByteOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		alignedByteOffset += formatByteSize;
	}

	i_oDevice.CreateInputLayout
	(
		vertexDescArray.data(),
		static_cast<UINT>(vertexDescArray.size()),
		i_oShaderFileBytes.data(),
		i_oShaderFileBytes.size(),
		&m_poInputLayout
	);
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
