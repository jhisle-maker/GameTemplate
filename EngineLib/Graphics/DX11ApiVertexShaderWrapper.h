#pragma once
#include "IApiVertexShaderWrapper.h"
#include <d3d11_4.h>

namespace GT
{
	class DX11ApiVertexShaderWrapper : public IApiVertexShaderWrapper
	{
	public:
		DX11ApiVertexShaderWrapper(ID3D11VertexShader& i_oVertexShader, ID3D11InputLayout& i_oInputLayout);
		~DX11ApiVertexShaderWrapper();

	public:
		inline ID3D11VertexShader* GetDX11VertexShader() const { return m_poVertexShader; }
		inline ID3D11InputLayout* GetDX11InputLayout() const { return m_poInputLayout; }

	private:
		ID3D11VertexShader* m_poVertexShader;
		ID3D11InputLayout* m_poInputLayout;
	};
}