#pragma once

#include "BaseComponent.h"

namespace GT
{
	class UpdatableComponent : BaseComponent
	{
	public:
		UpdatableComponent(const IContext& i_oContext) : BaseComponent(i_oContext) {}
		virtual ~UpdatableComponent() {};

		virtual void Update() = 0;
	};

	class DrawableComponent : UpdatableComponent
	{
	public:
		DrawableComponent(const IContext& i_oContext) : UpdatableComponent(i_oContext) {}
		virtual ~DrawableComponent() {};

		virtual void Draw() = 0;
	};
}
