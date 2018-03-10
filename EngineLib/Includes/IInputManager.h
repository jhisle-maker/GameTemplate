#pragma once

//START FORWARD DECL
namespace GT { class IKeyboardController; }
//END FORWARD DECL

namespace GT
{
	class IInputManager
	{
	public:
		IInputManager() {}
		virtual ~IInputManager() {}

	public:
		virtual IKeyboardController& GetKeyboardController() = 0;
	};
}