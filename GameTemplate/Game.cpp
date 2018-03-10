#include "pch.h"

#include "Game.h"
#include "IManagersFactory.h"
#include "IContentManager.h"
#include "IInputManager.h"
#include "IGraphicManager.h"
#include "IGraphicDevice.h"
#include "GameComponent.h"
#include "DrawableGameComponent.h"
#include "Color.h"

namespace GT
{
	Game::Game(const IManagersFactory& i_oManagersFactory)
		: m_poGraphicManager(nullptr)
		, m_poContentManager(nullptr)
		, m_poInputManager(nullptr)
		, m_oPreviousClockCount(0u)
		, m_fDeltaTime(0.0f)
		, m_poSpriteRendererComponent(nullptr)
	{
		i_oManagersFactory.CreateManagers(m_poGraphicManager, m_poContentManager, m_poInputManager);
	}

	Game::~Game()
	{
		//Nothing to do here
	}

	void Game::Init()
	{
		m_poSpriteRendererComponent = std::make_unique<SpriteRendererComponent>(*m_poInputManager, *m_poContentManager, *m_poGraphicManager);

		m_poSpriteRendererComponent->SetUpdateOrder(0u);
		m_poSpriteRendererComponent->SetUpdateOrder(0u);

		m_oGameComponentCollection.AddComponent(*m_poSpriteRendererComponent);

		m_oGameComponentCollection.Init();
	}

	void Game::LoadContent()
	{
		m_oGameComponentCollection.LoadContent();
	}

	void Game::DoLoop()
	{
		clock_t currentClock = clock();
		m_fDeltaTime = (currentClock - m_oPreviousClockCount) / static_cast<float>(CLOCKS_PER_SEC);
	
		m_oGameComponentCollection.Update(m_fDeltaTime);

		m_poGraphicManager->GetGraphicDevice().Clear(Color(100, 100, 100, 255));
		m_oGameComponentCollection.Draw(m_fDeltaTime);
		m_poGraphicManager->GetGraphicDevice().Present();

		m_oPreviousClockCount = currentClock;
	}

	void Game::OnScreenResolutionChanged(const size_t i_uiWidth, const size_t i_uiHeight)
	{
		m_poGraphicManager->OnScreenResolutionChanged(i_uiWidth, i_uiHeight);
	}

	void Game::OnSuspend()
	{
		m_poGraphicManager->OnSuspend();
	}

	void Game::OnResume()
	{
		//Nothing to do now
	}
}

