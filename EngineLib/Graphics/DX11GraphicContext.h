#pragma once
#include <wrl/client.h>
#include <d3d11_3.h>
#include "IGraphicContext.h"

//START FORWARD DECLS
namespace GT { class IApiVertexBuffer; }
//END FORWARD DECLS

namespace GT
{
	class DX11GraphicContext : public IGraphicContext
	{
	public:
		DX11GraphicContext(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice);
		virtual ~DX11GraphicContext();

	public:
		std::unique_ptr<IApiBufferWrapper> CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const;
		std::unique_ptr<IApiBufferWrapper> CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const;
	/*	void CreateApiVertexShader(const std::wstring& i_oShaderFileName, void*& o_oApiVertexShader) const;
		void CreateApiPixelShader(const std::wstring& i_oPixelShaderFileName, void*& o_oApiPixelShader) const;*/

		void ReleaseApiIndexBuffer(void*& i_oApiIndexBuffer) const;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_poDevice;
	};
}
