#include "pch.h"

#include "InputDeviceResources.h"
#include "Input\UWPKeyboardController.h"

namespace GT
{
	InputDeviceResources::InputDeviceResources(Windows::UI::Core::CoreWindow^ i_oWindow)
		: m_poKeyboardController(std::make_unique<UWPKeyboardController>(i_oWindow))
	{
		//Nothing to do here
	}

	InputDeviceResources::~InputDeviceResources()
	{
		//Nothing to do here
	}
}