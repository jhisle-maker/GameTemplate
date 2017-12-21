#pragma once

namespace GT
{
	class IPlayerController
	{
	public:
		IPlayerController() {}
		virtual ~IPlayerController() {}

	public:
		virtual bool FirePressed() const = 0;
		virtual bool ForwardPressed() const = 0;
		virtual bool BackPressed() const = 0;
		virtual bool JumpPressed() const = 0;
	};
}
