#include "pch.h"

#include "SpriteRendererComponent.h"
#include "IInputManager.h"
#include "IContentManager.h"
#include "IGraphicManager.h"
#include "ITexture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexPositionColorTexture.h"
#include "PerspectiveCamera.h"
#include "Effects\BasicEffect.h"
#include "IGraphicDevice.h"
#include "PrimitiveType.h"
#include "SamplerState.h"
#include "IKeyboardController.h"

namespace GT
{
	SpriteRendererComponent::SpriteRendererComponent(IInputManager& i_oInputManager, IContentManager& i_oContentManager, IGraphicManager& i_oGraphicManager)
		: m_oInputManager(i_oInputManager)
		, m_oContentManager(i_oContentManager)
		, m_oGraphicManager(i_oGraphicManager)
		, m_poTexture(nullptr)
		, m_poBasicEffect(nullptr)
		, m_poPerspectiveCamera(nullptr)
		, m_poSamplerState(nullptr)
		, m_oModelMatrix(Matrix::Identity)
	{
		//Nothing to do here
	}

	SpriteRendererComponent::~SpriteRendererComponent()
	{
		//Nothing to do here
	}

	void SpriteRendererComponent::Init()
	{
		//Create camera
		Vector3 eye(0.0f, 0.0f, 5.0f);
		Vector3 at(0.0f, 0.0f, 0.0f);
		Vector3 up(0.0f, 1.0f, 0.0f);

		float fAspectRatio = m_oGraphicManager.GetScreenAspectRatio();
		float fGradFovY = 70.0f;

		m_poPerspectiveCamera = std::make_unique<PerspectiveCamera>(fAspectRatio, fGradFovY, eye, at, up);

		//Create sampler
		m_poSamplerState = std::make_unique<SamplerState>(m_oGraphicManager.GetGraphicContext());
	}

	void SpriteRendererComponent::LoadContent()
	{
		//Load Texture
		m_poTexture = &m_oContentManager.LoadTexture("test.png");

		//Create Buffer for sprite
		VertexPositionColorTexture textureQuadData[] =
		{
			{ Vector3(-0.5f, -0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(0.0f, 1.0f) },
			{ Vector3(-0.5f,  0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(0.0f, 0.0f) },
			{ Vector3( 0.5f,  0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(1.0f, 0.0f) },
			{ Vector3( 0.5f, -0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(1.0f, 1.0f) },
			{ Vector3(2.0f, -0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(0.0f, 1.0f) },
			{ Vector3(2.0f,  0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(0.0f, 0.0f) },
			{ Vector3(3.0f,  0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(1.0f, 0.0f) },
			{ Vector3(3.0f, -0.5f, 1.0f), Color(0, 0, 0, 255), Vector2(1.0f, 1.0f) }
		};

		uint16_t quadIndices[] =
		{
			0,1,2, // -x
			2,3,0,
			4,5,6, // -x
			6,7,4,
		};

		m_poQuadVB = std::make_unique<VertexBuffer<VertexPositionColorTexture>>(textureQuadData, 8, m_oGraphicManager.GetGraphicContext());
		m_poQuadIB = std::make_unique<IndexBuffer<uint16_t>>(quadIndices, 12, m_oGraphicManager.GetGraphicContext());

		m_poBasicEffect = std::make_unique<BasicEffect>(m_oGraphicManager, m_oContentManager);
	}

	void SpriteRendererComponent::Update(const float i_fDeltaTime)
	{
		static float x = 0.0f;

		if (m_oInputManager.GetKeyboardController().IsKeyPressed(Key::Left))
		{
			x -= 1.0f;
			m_oModelMatrix.SetTranslation(Vector3(x, 0.0f, 0.0f));
		}
		
		if (m_oInputManager.GetKeyboardController().IsKeyPressed(Key::Right))
		{
			x += 1.0f;
			m_oModelMatrix.SetTranslation(Vector3(x, 0.0f, 0.0f));
		}
	}

	void SpriteRendererComponent::Draw(const float i_fDeltaTime)
	{
		m_poBasicEffect->SetModel(m_oModelMatrix);
		m_poBasicEffect->SetView(m_poPerspectiveCamera->GetView());
		m_poBasicEffect->SetProjection(m_poPerspectiveCamera->GetProjection());
		m_poBasicEffect->SetTextureEnabled(true);
		m_poBasicEffect->SetTexture(*m_poTexture);
		m_poBasicEffect->SetTextureSampler(*m_poSamplerState);

		m_poBasicEffect->Apply();

		m_oGraphicManager.GetGraphicDevice().SetIndexBuffer(*m_poQuadIB);
		m_oGraphicManager.GetGraphicDevice().SetVertexBuffer(*m_poQuadVB);
		m_oGraphicManager.GetGraphicDevice().DrawIndexed(PrimitiveType::eTRIANGLE_LIST, 12, 0u, 0u);
	}
}