#include "GameComponentCollection.h"
#include "GameComponent.h"
#include "DrawableGameComponent.h"
#include <algorithm>

namespace GT
{
	GameComponentCollection::GameComponentCollection()
	{
		m_oToBeRenderedComponents.reserve(100);
		m_oToBeUpdatedComponents.reserve(100);
	}

	GameComponentCollection::~GameComponentCollection()
	{
		//Nothing to do here
	}

	void GameComponentCollection::AddComponent(GameComponent& i_oComponent)
	{
		m_oToBeUpdatedComponents.push_back(&i_oComponent);
		std::sort(m_oToBeUpdatedComponents.begin(), m_oToBeUpdatedComponents.end(), [](const GameComponent* a, const GameComponent* b) -> bool
		{ 
			return a->GetUpdateOrder() < b->GetUpdateOrder(); 
		});
	}

	void GameComponentCollection::AddComponent(DrawableGameComponent& i_oDrawableGameComponent)
	{
		m_oToBeUpdatedComponents.push_back(&i_oDrawableGameComponent);
		m_oToBeRenderedComponents.push_back(&i_oDrawableGameComponent);

		std::sort(m_oToBeUpdatedComponents.begin(), m_oToBeUpdatedComponents.end(), [](const GameComponent* a, const GameComponent* b) -> bool
		{
			return a->GetUpdateOrder() < b->GetUpdateOrder();
		});

		std::sort(m_oToBeRenderedComponents.begin(), m_oToBeRenderedComponents.end(), [](const DrawableGameComponent* a, const DrawableGameComponent* b) -> bool
		{
			return a->GetDrawOrder() < b->GetDrawOrder();
		});
	}

	void GameComponentCollection::Init()
	{
		std::for_each(m_oToBeUpdatedComponents.begin(), m_oToBeUpdatedComponents.end(), [](GameComponent* poComponent)
		{
			poComponent->Init();
		});
	}

	void GameComponentCollection::LoadContent()
	{
		std::for_each(m_oToBeUpdatedComponents.begin(), m_oToBeUpdatedComponents.end(), [](GameComponent* poComponent)
		{
			poComponent->LoadContent();
		});
	}

	void GameComponentCollection::Update(const float i_fDeltaTime)
	{
		std::for_each(m_oToBeUpdatedComponents.begin(), m_oToBeUpdatedComponents.end(), [i_fDeltaTime](GameComponent* poComponent)
		{
			poComponent->Update(i_fDeltaTime);
		});
	}

	void GameComponentCollection::Draw(const float i_fDeltaTime)
	{
		std::for_each(m_oToBeRenderedComponents.begin(), m_oToBeRenderedComponents.end(), [i_fDeltaTime](DrawableGameComponent* poComponent)
		{
			poComponent->Draw(i_fDeltaTime);
		});
	}
}