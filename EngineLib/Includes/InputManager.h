#pragma once

#include "IInputManager.h"
#include <memory>

//START FORWARD DECL
namespace GT { class IKeyboardController; }
//END FORWARD DECL

namespace GT
{
	class InputManager : public IInputManager
	{
	public:
		InputManager(IKeyboardController* i_oKeyboardController);
		~InputManager();

	public:
		inline IKeyboardController & GetKeyboardController() { return *m_poKeyboardController; }
		inline const IKeyboardController& GetKeyboardController() const { return *m_poKeyboardController; }

	private:
		InputManager(const InputManager& i_oOther) = delete;
		InputManager& operator=(const InputManager& i_oOther) = delete;

	private:
		std::unique_ptr<IKeyboardController> m_poKeyboardController;
	};
}