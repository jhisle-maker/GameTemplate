#include "InputManager.h"
#include "IKeyboardController.h"

namespace GT
{
	InputManager::InputManager(IKeyboardController* i_poKeyboardController)
		: m_poKeyboardController(i_poKeyboardController)
	{
		//Nothing to do here
	}

	InputManager::~InputManager()
	{
		//Nothing to do here
	}
}