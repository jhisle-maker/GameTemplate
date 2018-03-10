#pragma once

namespace GT
{
	enum Key
	{
		W,
		A,
		S,
		D,
		Up,
		Down,
		Left,
		Right
	};

	class IKeyboardController
	{
	public:
		IKeyboardController() {}
		virtual ~IKeyboardController() {}

		virtual bool IsKeyPressed(Key key) const = 0;
		virtual bool IsKeyReleased(Key key) const = 0;
	};
}
