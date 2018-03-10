#pragma once

#include <memory>
#include <vector>
#include <ctime>
#include <iostream>
#include "GameComponentCollection.h"

//Components
#include "Component\SpriteRendererComponent.h"

//START FORWARD DECLS
namespace GT { class IManagersFactory; }
namespace GT { class IInputManager; }
namespace GT { class IContentManager; }
namespace GT { class IGraphicManager; }
//END FORWARD DECLS

namespace GT
{
	class Game
	{
	public:
		Game(const IManagersFactory& i_oManagersFactory);
		~Game();

	public:
		void Init();
		void LoadContent();
		void DoLoop();

		void OnScreenResolutionChanged(const size_t i_uiWidth, const size_t i_uiHeight);
		void OnSuspend();
		void OnResume();

	private:
		Game(const Game& i_oOther) = delete;
		Game& operator=(const Game& i_oOther) = delete;

	private:
		std::unique_ptr<IGraphicManager> m_poGraphicManager;
		std::unique_ptr<IContentManager> m_poContentManager;
		std::unique_ptr<IInputManager> m_poInputManager;

		GameComponentCollection m_oGameComponentCollection;

		clock_t m_oPreviousClockCount;
		float m_fDeltaTime;

	private: //Game Components
		std::unique_ptr<DrawableGameComponent> m_poSpriteRendererComponent;
	};
}