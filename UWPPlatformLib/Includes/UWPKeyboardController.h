#pragma once

#include "IKeyboardController.h"
#include <agile.h>
#include <map>

using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;

namespace GT
{
	class UWPKeyboardController : public IKeyboardController
	{
	public:
		UWPKeyboardController(CoreWindow^ window);
		~UWPKeyboardController();

	public:
		bool IsKeyPressed(const Key key) const;
		bool IsKeyReleased(const Key key) const;

	private:
		ref class UWPKeyEventHandler
		{
		internal:
			UWPKeyEventHandler(CoreWindow^ i_oWindow);

		internal:
			bool IsKeyUp(Key key);
			bool IsKeyDown(Key key);

		private:
			VirtualKey Convert(const Key key) const;

		private:
			Platform::Agile<CoreWindow> m_oWindow;
		};

		UWPKeyEventHandler^ m_oKeyEventHandler;
		std::map<Key, bool> m_oPressedKeyMap;
	};
}