#include "pch.h"
#include "UWPKeyboardController.h"

using namespace Windows::Foundation;
using namespace Windows::System;


namespace GT
{
	UWPKeyboardController::UWPKeyboardController(CoreWindow^ window)
	{
		keyEventHandler = ref new UWPKeyEventHandler(m_oPressedKeyMap);

		window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(keyEventHandler, &UWPKeyEventHandler::OnKeyUp);
		window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(keyEventHandler, &UWPKeyEventHandler::OnKeyDown);
	}

	UWPKeyboardController::~UWPKeyboardController()
	{
		//Nothing to do here
	}


	bool UWPKeyboardController::IsKeyPressed(Key key) const
	{
		std::map<Key, bool>::const_iterator it = m_oPressedKeyMap.find(key);
		if (it != m_oPressedKeyMap.cend())
		{
			return m_oPressedKeyMap.at(key) == true;
		}

		return false;
	}

	bool UWPKeyboardController::IsKeyReleased(Key key) const
	{
		std::map<Key, bool>::const_iterator it = m_oPressedKeyMap.find(key);
		if (it != m_oPressedKeyMap.cend())
		{
			return m_oPressedKeyMap.at(key) == false;
		}

		return false;
	}

	UWPKeyboardController::UWPKeyEventHandler::UWPKeyEventHandler(std::map<Key, bool>& i_oPressedKeyMap)
		: m_oPressedKeyMap(i_oPressedKeyMap)
	{
		//Nothing to do here
	}

	void UWPKeyboardController::UWPKeyEventHandler::OnKeyUp(CoreWindow^ window, KeyEventArgs^ args)
	{
		switch (args->VirtualKey)
		{
		case VirtualKey::W: m_oPressedKeyMap[Key::W] = false; break;
		case VirtualKey::A: m_oPressedKeyMap[Key::A] = false; break;
		case VirtualKey::S: m_oPressedKeyMap[Key::S] = false; break;
		case VirtualKey::D: m_oPressedKeyMap[Key::D] = false; break;
		case VirtualKey::Up: m_oPressedKeyMap[Key::Up] = false; break;
		case VirtualKey::Down: m_oPressedKeyMap[Key::Down] = false; break;
		case VirtualKey::Left: m_oPressedKeyMap[Key::Left] = false; break;
		case VirtualKey::Right: m_oPressedKeyMap[Key::Right] = false; break;
		}
	}

	void UWPKeyboardController::UWPKeyEventHandler::OnKeyDown(CoreWindow^ window, KeyEventArgs^ args)
	{
		switch (args->VirtualKey)
		{
		case VirtualKey::W: m_oPressedKeyMap[Key::W] = true; break;
		case VirtualKey::A: m_oPressedKeyMap[Key::A] = true; break;
		case VirtualKey::S: m_oPressedKeyMap[Key::S] = true; break;
		case VirtualKey::D: m_oPressedKeyMap[Key::D] = true; break;
		case VirtualKey::Up: m_oPressedKeyMap[Key::Up] = true; break;
		case VirtualKey::Down: m_oPressedKeyMap[Key::Down] = true; break;
		case VirtualKey::Left: m_oPressedKeyMap[Key::Left] = true; break;
		case VirtualKey::Right: m_oPressedKeyMap[Key::Right] = true; break;
		}
	}
}
