#pragma once

namespace GT
{
	class GameComponent
	{
	public:
		GameComponent();
		virtual ~GameComponent() {};

		virtual void Init() = 0;
		virtual void LoadContent() = 0;
		virtual void Update(const float i_fDeltaTime) = 0;

		inline const size_t GetUpdateOrder() const { return m_uiUpdateOrder; }
		inline void SetUpdateOrder(unsigned int i_uiUpdateOrder) { m_uiUpdateOrder = i_uiUpdateOrder; }

	private:
		size_t m_uiUpdateOrder;
	};
}
