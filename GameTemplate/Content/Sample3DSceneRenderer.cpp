#include "pch.h"
#include <ppltasks.h>

#include "Sample3DSceneRenderer.h"
#include "Graphics\VertexBuffer.h"
#include "Graphics\IndexBuffer.h"
#include "Graphics\ConstBuffer.h"
#include "Graphics\PixelShader.h"
#include "Graphics\VertexShader.h"
#include "Graphics\SamplerState.h"

#include "Services\IServicesContext.h"

#include "Graphics\DX11GraphicDevice.h"
#include "Graphics\DX11GraphicContext.h"
#include "Math\Vector3.h"
#include "Math\Matrix.h"
#include "Services\UWPFileLoaderService.h"
#include "Services\WicColorTexture2DLoaderService.h"

using namespace GT;
using namespace DirectX;
using namespace Windows::Foundation;
using namespace Windows::Storage;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources, const GT::IGraphicDevice& i_oGraphicDevice, const GT::IGraphicContext& i_oGraphicContext, const GT::IServicesContext& i_oServicesContext) 
	: m_oGraphicDevice(i_oGraphicDevice)
	, m_oGraphicContext(i_oGraphicContext)
	, m_oServicesContext(i_oServicesContext)
	, m_loadingComplete(false)
	, m_degreesPerSecond(45)
	, m_indexCount(0)
	, m_tracking(false)
	, m_deviceResources(deviceResources)
	, m_poIndexBuffer(nullptr)
	, m_poVertexBuffer(nullptr)
	, m_poTexture(nullptr)
	, m_poVertexShader(nullptr)
	, m_poPixelShader(nullptr)
	, m_poCamera(nullptr)
{	
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	Vector3 eye(0.0, 0.7f, 1.5f);
	Vector3 at(0.0, -0.1f, 0.0f);
	Vector3 up(0.0, 1.0, 0.0f);

	m_poCamera = std::make_unique<ProjectionCamera>(aspectRatio, 70.0f, eye, at, up);

	m_constantBufferData.model = Matrix::Identity;
	m_constantBufferData.projection = m_poCamera->GetProjection();
	m_constantBufferData.view = m_poCamera->GetView();
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	// Convert degrees to radians, then convert seconds to rotation angle
	float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
	double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
	float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

	m_constantBufferData.model = Matrix::Transpose(Matrix::RotationY(radians));
}


// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	m_poConstBuffer->Update(m_constantBufferData);

	m_poVertexShader->BindConstantBuffer(*m_poConstBuffer);
	
	m_poPixelShader->BindTexture(*m_poTexture);
	m_poPixelShader->BindSamplerState(*m_poSamplerState);

	m_oGraphicDevice.SetVertexBuffer(*m_poVertexBuffer);
	m_oGraphicDevice.SetIndexBuffer(*m_poIndexBuffer);
	m_oGraphicDevice.BindVertexShader(*m_poVertexShader);
	m_oGraphicDevice.BindPixelShader(*m_poPixelShader);
	

	// Draw the objects.
	auto context = m_deviceResources->GetD3DDeviceContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexed(m_indexCount, 0, 0);
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	using namespace Concurrency;


	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createResourcesTask = create_task([this]() 
	{
		m_poVertexShader = m_oServicesContext.GetShaderLoaderService().LoadVertexShader("PositionColorTextureVertexShader.cso", VertexPositionColorTexture::VertexDeclaration);
		m_poPixelShader = m_oServicesContext.GetShaderLoaderService().LoadPixelShader("PositionColorTexturePixelShader.cso");

		m_poConstBuffer = std::make_unique<ConstBuffer<ModelViewProjectionData>>(m_constantBufferData, m_oGraphicContext);
		m_poSamplerState = std::make_unique<GT::SamplerState>(m_oGraphicContext);
	});

	// Once both shaders are loaded, create the mesh.
	auto createQuadTask = (createResourcesTask).then([this] () 
	{
		static const VertexPositionColorTexture quadVertices[] = 
		{
			{Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
			{Vector3(-0.5f,  0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },
			{Vector3( 0.5f,  0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
			{Vector3( 0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) },
		};

		m_poVertexBuffer = std::make_unique<VertexBuffer<VertexPositionColorTexture>>(quadVertices, 4, m_oGraphicContext);

		static const unsigned short quadIndices [] =
		{
			0,1,2, // -x
			2,3,0,
		};

		m_poIndexBuffer = std::make_unique<GT::IndexBuffer<USHORT>>(quadIndices, 6, m_oGraphicContext);
		m_indexCount = ARRAYSIZE(quadIndices);
	});

	createQuadTask.then([this]()
	{
		m_poTexture = m_oServicesContext.GetTextureLoaderService().Load("test.png");
		m_loadingComplete = true;
	});
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}