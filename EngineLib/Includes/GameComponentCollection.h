#pragma once

#include <vector>

//START FORWARD DECLS
namespace GT { class GameComponent; }
namespace GT { class DrawableGameComponent; }
//END FORWARD DECLS

namespace GT
{
	class GameComponentCollection
	{
	public:
		GameComponentCollection();
		~GameComponentCollection();

		void AddComponent(GameComponent& i_oComponent);
		void AddComponent(DrawableGameComponent& i_oDrawableGameComponent);

		void Init();
		void LoadContent();
		void Update(const float i_fDeltaTime);
		void Draw(const float i_fDeltaTime);

		inline const std::vector<GameComponent*>& GetToBeUpdatedComponents() const { return m_oToBeUpdatedComponents; }
		inline const std::vector<DrawableGameComponent*>& GetToBeRenderedComponents() const { return m_oToBeRenderedComponents; }

	private:
		std::vector<GameComponent*> m_oToBeUpdatedComponents;
		std::vector<DrawableGameComponent*> m_oToBeRenderedComponents;
	};
}
