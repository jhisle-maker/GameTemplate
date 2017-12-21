#pragma once

#include <memory>

namespace GT { class IKeyboardController; }

namespace GT
{
	class InputDeviceResources
	{
	public:
		InputDeviceResources(Windows::UI::Core::CoreWindow^ i_oWindow);
		~InputDeviceResources();

	private:
		InputDeviceResources(const InputDeviceResources& i_oOther) = delete;
		InputDeviceResources& operator= (const InputDeviceResources& i_oOther) = delete;

	public:
		IKeyboardController& GetKeyboardController() const { return *m_poKeyboardController; }

	private:
		std::unique_ptr<IKeyboardController> m_poKeyboardController;
	};
}
