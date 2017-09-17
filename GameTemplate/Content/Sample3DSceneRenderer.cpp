#include "pch.h"
#include <ppltasks.h>

#include "Sample3DSceneRenderer.h"
#include "Graphics\VertexBuffer.h"
#include "Graphics\IndexBuffer.h"
#include "Graphics\ConstBuffer.h"
#include "Graphics\VertexShader.h"
#include "Graphics\PixelShader.h"
#include "Graphics\DX11GraphicDevice.h"
#include "Graphics\DX11GraphicContext.h"
#include "Math\Vector3.h"
#include "Math\Matrix.h"
#include "FileLoader\UWPFileLoader.h"
#include "Loaders\WicColorTexture2DLoader.h"


using namespace GameTemplate;

using namespace DirectX;
using namespace Windows::Foundation;
using namespace Windows::Storage;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources, const GT::IGraphicDevice& i_oGraphicDevice, const GT::IGraphicContext& i_oGraphicContext, const GT::IFileLoader& i_oFileLoader) 
	: m_oGraphicDevice(i_oGraphicDevice)
	, m_oGraphicContext(i_oGraphicContext)
	, m_oFileLoader(i_oFileLoader)
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

	GT::Vector3 eye(0.0, 0.7f, 1.5f);
	GT::Vector3 at(0.0, -0.1f, 0.0f);
	GT::Vector3 up(0.0, 1.0, 0.0f);

	m_poCamera = std::unique_ptr<GT::SimpleCamera>(new GT::SimpleCamera(aspectRatio, 70.0f, eye, at, up));

	m_constantBufferData.model = GT::Matrix::Identity;
	m_constantBufferData.projection = m_poCamera->GetProjection();
	m_constantBufferData.view = m_poCamera->GetView();
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(radians);
	}
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	m_constantBufferData.model = GT::Matrix::Transpose(GT::Matrix::RotationY(radians));
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationX(radians)));
}

void Sample3DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
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

	// Load shaders asynchronously.
	auto loadVertexShaderBufTask = create_task([this]() -> std::vector<byte>
	{ 
		Platform::String^ path = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;

		std::vector<byte> vertexShaderBuf;
		m_oFileLoader.Load("PositionColorTextureVertexShader.cso", vertexShaderBuf);
		return vertexShaderBuf;
	});

	auto loadPixelShaderBufTask = create_task([this]() -> std::vector<byte>
	{
		std::vector<byte> pixelShaderBuf;
		m_oFileLoader.Load("PositionColorTexturePixelShader.cso", pixelShaderBuf);
	
		return pixelShaderBuf;
	});

	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask = loadVertexShaderBufTask.then([this](std::vector<byte>& vertexShaderBuf) 
	{
		m_poVertexShader = std::unique_ptr<GT::IVertexShader>(new GT::VertexShader<VertexPositionColorTexture>(vertexShaderBuf, m_oGraphicContext));
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask = loadPixelShaderBufTask.then([this](std::vector<byte>& pixelShaderBuf) 
	{
		m_poPixelShader = std::unique_ptr<GT::IPixelShader>(new GT::PixelShader(pixelShaderBuf, m_oGraphicContext));
		m_poConstBuffer = std::unique_ptr<GT::ConstBuffer<ModelViewProjectionConstantBuffer>>(new GT::ConstBuffer<ModelViewProjectionConstantBuffer>(m_constantBufferData, m_oGraphicContext));
	});

	// Once both shaders are loaded, create the mesh.
	auto createCubeTask = (createPSTask && createVSTask).then([this] () {

		// Load mesh vertices. Each vertex has a position and a color.
		/*static const VertexPositionColorTexture cubeVertices[] = 
		{
			{GT::Vector3(-0.5f, -0.5f, -0.5f), GT::Vector3(0.0f, 0.0f, 0.0f), GT::Vector2(0.0f, 0.0f) },
			{GT::Vector3(-0.5f, -0.5f,  0.5f), GT::Vector3(0.0f, 0.0f, 1.0f), GT::Vector2(0.0f, 0.0f) },
			{GT::Vector3(-0.5f,  0.5f, -0.5f), GT::Vector3(0.0f, 1.0f, 0.0f), GT::Vector2(0.0f, 1.0f) },
			{GT::Vector3(-0.5f,  0.5f,  0.5f), GT::Vector3(0.0f, 1.0f, 1.0f), GT::Vector2(0.0f, 0.0f) },
			{GT::Vector3( 0.5f, -0.5f, -0.5f), GT::Vector3(1.0f, 0.0f, 0.0f), GT::Vector2(0.0f, 0.0f) },
			{GT::Vector3( 0.5f, -0.5f,  0.5f), GT::Vector3(1.0f, 0.0f, 1.0f), GT::Vector2(0.0f, 0.0f) },
			{GT::Vector3( 0.5f,  0.5f, -0.5f), GT::Vector3(1.0f, 1.0f, 0.0f), GT::Vector2(1.0f, 0.0f) },
			{GT::Vector3( 0.5f,  0.5f,  0.5f), GT::Vector3(1.0f, 1.0f, 1.0f), GT::Vector2(0.0f, 0.0f) },
		};*/

		static const VertexPositionColorTexture quadVertices[] = 
		{
			{GT::Vector3(-0.5f, -0.5f, 0.0f), GT::Vector3(0.0f, 0.0f, 0.0f), GT::Vector2(0.0f, 1.0f) },
			{GT::Vector3(-0.5f,  0.5f, 0.0f), GT::Vector3(0.0f, 0.0f, 0.0f), GT::Vector2(0.0f, 0.0f) },
			{GT::Vector3( 0.5f,  0.5f, 0.0f), GT::Vector3(0.0f, 0.0f, 0.0f), GT::Vector2(1.0f, 0.0f) },
			{GT::Vector3( 0.5f, -0.5f, 0.0f), GT::Vector3(0.0f, 0.0f, 0.0f), GT::Vector2(1.0f, 1.0f) },
		};

		m_poVertexBuffer = std::unique_ptr<GT::VertexBuffer<VertexPositionColorTexture>>(new GT::VertexBuffer<VertexPositionColorTexture>(quadVertices, 4, m_oGraphicContext));

		// Load mesh indices. Each trio of indices represents
		// a triangle to be rendered on the screen.
		// For example: 0,2,1 means that the vertices with indexes
		// 0, 2 and 1 from the vertex buffer compose the 
		// first triangle of this mesh.
		//static const unsigned short cubeIndices [] =
		//{
		//	0,2,1, // -x
		//	1,2,3,

		//	4,5,6, // +x
		//	5,7,6,

		//	0,1,5, // -y
		//	0,5,4,

		//	2,6,7, // +y
		//	2,7,3,

		//	0,4,6, // -z
		//	0,6,2,

		//	1,3,7, // +z
		//	1,7,5,
		//};

		static const unsigned short quadIndices [] =
		{
			0,1,2, // -x
			2,3,0,
		};

		m_poIndexBuffer = std::unique_ptr<GT::IndexBuffer<USHORT>>(new GT::IndexBuffer<USHORT>(quadIndices, 6, m_oGraphicContext));
		m_indexCount = ARRAYSIZE(quadIndices);
	});

	// Once the cube is loaded, the object is ready to be rendered.
	createCubeTask.then([this]() 
	{
		std::vector<GT::Color> textureData;
		textureData.push_back(GT::Color(255, 0, 0, 0));
		textureData.push_back(GT::Color(0, 255, 0, 0));
		textureData.push_back(GT::Color(0, 0, 255, 0));
		//textureData.push_back(GT::Color(0, 0, 255, 0));

		size_t asd = sizeof(GT::Color);

		GT::WicColorTexture2DLoader loader(m_oFileLoader, m_oGraphicContext);
		m_poTexture = loader.Load("test.png");

		//m_poTexture = std::unique_ptr<GT::ITexture>(new GT::Texture2D(textureData, 3, 1, m_oGraphicContext));

		m_loadingComplete = true;
	});
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}