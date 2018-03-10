#pragma once

#include "GameComponent.h"

namespace GT
{
	class DrawableGameComponent : public GameComponent
	{
	public:
		DrawableGameComponent();
		virtual ~DrawableGameComponent() {};

		virtual void Draw(const float i_fDeltaTime) = 0;

		inline const size_t GetDrawOrder() const { return m_uiDrawOrder; }
		inline void SetDrawOrder(unsigned int i_uiDrawOrder) { m_uiDrawOrder = i_uiDrawOrder; }

	private:
		unsigned int m_uiDrawOrder;
	};
}
