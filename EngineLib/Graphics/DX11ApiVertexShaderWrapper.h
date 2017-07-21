#pragma once
#include <d3d11_4.h>
#include <vector>

#include "IApiGraphicResourceWrapper.h"

//START FORWARD DECLS
namespace GT { struct VertexDeclaration; }
//END FORWARD DECLS

namespace GT
{
	class DX11ApiVertexShaderWrapper : public IApiGraphicResourceWrapper
	{
	public:
		DX11ApiVertexShaderWrapper(ID3D11Device& i_oDevice, const std::vector<uint8_t>& i_oShaderFileBytes, const VertexDeclaration& vertexDeclaration);
		~DX11ApiVertexShaderWrapper();

	public:
		inline ID3D11VertexShader* GetDX11VertexShader() const { return m_poVertexShader; }
		inline ID3D11InputLayout* GetDX11InputLayout() const { return m_poInputLayout; }

	private:
		ID3D11VertexShader* m_poVertexShader;
		ID3D11InputLayout* m_poInputLayout;
	};
}