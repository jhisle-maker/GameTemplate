#pragma once

#include "DrawableGameComponent.h"
#include "Matrix.h"
#include <memory>

//START FORWARD DECLS
namespace GT { class IInputManager; }
namespace GT { class IContentManager; }
namespace GT { class IGraphicManager; }
namespace GT { class ITexture; }
namespace GT { class IVertexBuffer; }
namespace GT { class IIndexBuffer; }
namespace GT { class PerspectiveCamera; }
namespace GT { class BasicEffect; }
namespace GT { class ISamplerState; }
//END FORWARD DECLS

namespace GT
{
	class SpriteRendererComponent : public DrawableGameComponent
	{
	public:
		SpriteRendererComponent(IInputManager& i_oInputManager, IContentManager& i_oContentManager, IGraphicManager& i_oGraphicManager);
		~SpriteRendererComponent();

	public:
		void Init();
		void LoadContent();

		void Update(const float i_fDeltaTime);
		void Draw(const float i_fDeltaTime);

	private:
		IInputManager& m_oInputManager;
		IContentManager& m_oContentManager;
		IGraphicManager& m_oGraphicManager;

		ITexture* m_poTexture;
		Matrix m_oModelMatrix;

		std::unique_ptr<ISamplerState> m_poSamplerState;
		std::unique_ptr<BasicEffect> m_poBasicEffect;
		std::unique_ptr<PerspectiveCamera> m_poPerspectiveCamera;
		std::unique_ptr<IVertexBuffer> m_poQuadVB;
		std::unique_ptr<IIndexBuffer> m_poQuadIB;
	};
}