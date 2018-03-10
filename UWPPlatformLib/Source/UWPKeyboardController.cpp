#include "pch.h"
#include "UWPKeyboardController.h"

using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Core;


namespace GT
{
	UWPKeyboardController::UWPKeyboardController(CoreWindow^ window)
	{
		m_oKeyEventHandler = ref new UWPKeyEventHandler(window);
	}

	UWPKeyboardController::~UWPKeyboardController()
	{
		//Nothing to do here
	}


	bool UWPKeyboardController::IsKeyPressed(const Key key) const
	{
		return m_oKeyEventHandler->IsKeyDown(key);
	}

	bool UWPKeyboardController::IsKeyReleased(const Key key) const
	{
		return m_oKeyEventHandler->IsKeyUp(key);
	}

	UWPKeyboardController::UWPKeyEventHandler::UWPKeyEventHandler(CoreWindow^ i_oWindow)
		: m_oWindow(i_oWindow)
	{
		//Nothing to do here
	}

	bool UWPKeyboardController::UWPKeyEventHandler::IsKeyUp(Key key)
	{
		VirtualKey virtualKey = Convert(key);

		CoreVirtualKeyStates keyState = m_oWindow->GetKeyState(virtualKey);
		return keyState != CoreVirtualKeyStates::Down && keyState == (CoreVirtualKeyStates::Down | CoreVirtualKeyStates::Locked);
	}

	bool UWPKeyboardController::UWPKeyEventHandler::IsKeyDown(Key key)
	{
		VirtualKey virtualKey = Convert(key);

		CoreVirtualKeyStates keyState = m_oWindow->GetKeyState(virtualKey);
		return keyState == CoreVirtualKeyStates::Down || keyState == (CoreVirtualKeyStates::Down | CoreVirtualKeyStates::Locked);
	}

	VirtualKey UWPKeyboardController::UWPKeyEventHandler::Convert(const Key key) const 
	{
		VirtualKey virtualKey = VirtualKey::None;

		switch (key)
		{
		case Key::W: virtualKey = VirtualKey::W; break;
		case Key::A: virtualKey = VirtualKey::A; break;
		case Key::S: virtualKey = VirtualKey::S; break;
		case Key::D: virtualKey = VirtualKey::D; break;
		case Key::Up: virtualKey = VirtualKey::Up; break;
		case Key::Down: virtualKey = VirtualKey::Down; break;
		case Key::Left: virtualKey = VirtualKey::Left; break;
		case Key::Right: virtualKey = VirtualKey::Right; break;
		}

		return virtualKey;
	}
}
