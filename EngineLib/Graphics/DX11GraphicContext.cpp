#pragma once
#include "DX11GraphicContext.h"
#include "DX11ApiVertexBuffer.h"
#include "DX11ApiIndexBuffer.h"

#include <wrl/client.h>
#include <d3d11_3.h>
#include <stdint.h>

namespace GT
{
	DX11GraphicContext::DX11GraphicContext(const Microsoft::WRL::ComPtr<ID3D11Device> i_poDevice)
		: m_poDevice(i_poDevice)
	{
		//Nothing to do here
	}

	DX11GraphicContext::~DX11GraphicContext()
	{
		//Nothing to do here
	}

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiVertexBuffer(const void* i_paoVertexData, const size_t i_uiVertexSize, const size_t i_uiElementsCount) const
	{
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = i_paoVertexData;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(static_cast<uint32_t>(i_uiVertexSize * i_uiElementsCount), D3D11_BIND_VERTEX_BUFFER);

		ID3D11Buffer* poBuffer = nullptr;
		m_poDevice->CreateBuffer
		(
			&vertexBufferDesc,
			&vertexBufferData,
			&poBuffer
		);

		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiVertexBuffer(poBuffer)));
	}

	std::unique_ptr<IApiBufferWrapper> DX11GraphicContext::CreateApiIndexBuffer(const void* i_paoIndexData, const size_t i_uiIndexSize, const size_t i_uiElementsCount) const
	{
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = i_paoIndexData;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC indexBufferDesc(static_cast<uint32_t>(i_uiIndexSize * i_uiElementsCount), D3D11_BIND_INDEX_BUFFER);
		
		ID3D11Buffer* poBuffer = nullptr;
		m_poDevice->CreateBuffer
		(
			&indexBufferDesc,
			&indexBufferData,
			&poBuffer
		);

		return std::move(std::unique_ptr<IApiBufferWrapper>(new DX11ApiIndexBuffer(poBuffer)));
	}
	
	void DX11GraphicContext::ReleaseApiIndexBuffer(void*& i_oApiIndexBuffer) const
	{
		if (i_oApiIndexBuffer != nullptr)
		{
			reinterpret_cast<ID3D11Buffer*>(i_oApiIndexBuffer)->Release();
		}
	}

	//void DX11GraphicContext::CreateApiVertexShader(const std::wstring& i_oShaderFileName, void*& o_oApiVertexShader) const
	//{
	//	/*auto loadVSTask = GT::ReadDataAsync(L"SampleVertexShader.cso");

	//	auto createShaderTask = loadVSTask.then([this, &o_oApiVertexShader](const std::vector<byte>& fileData)
	//	{
	//		m_poDevice->CreateVertexShader
	//		(
	//			&fileData[0],
	//			fileData.size(),
	//			nullptr,
	//			reinterpret_cast<ID3D11VertexShader**>(&o_oApiVertexShader)
	//		);
	//	});

	//	createShaderTask.wait();*/
	//}

	//void DX11GraphicContext::CreateApiPixelShader(const std::wstring& i_oPixelShaderFileName, void*& o_oApiPixelShader) const
	//{
	//	/*auto loadVSTask = GT::ReadDataAsync(L"SampleVertexShader.cso");

	//	auto createShaderTask = loadVSTask.then([this, &o_oApiPixelShader](const std::vector<byte>& fileData)
	//	{
	//		m_poDevice->CreateVertexShader
	//		(
	//			&fileData[0],
	//			fileData.size(),
	//			nullptr,
	//			reinterpret_cast<ID3D11VertexShader**>(&o_oApiPixelShader)
	//		);
	//	});

	//	createShaderTask.wait();*/
	//}
}
