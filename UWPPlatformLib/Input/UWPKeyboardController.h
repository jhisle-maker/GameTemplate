#pragma once

#include "Input\IKeyboardController.h"
#include <map>

using namespace Windows::UI::Core;
using namespace Windows::UI::Input;

namespace GT
{
	class UWPKeyboardController : public IKeyboardController
	{
	public:
		UWPKeyboardController(CoreWindow^ window);
		~UWPKeyboardController();

	public:
		bool IsKeyPressed(Key key) const;
		bool IsKeyReleased(Key key) const;

	private:
		ref class UWPKeyEventHandler
		{
		internal:
			UWPKeyEventHandler(std::map<Key, bool>& m_oPressedKeyMap);

		public:
			void OnKeyUp(CoreWindow^ window, KeyEventArgs^ args);
			void OnKeyDown(CoreWindow^ window, KeyEventArgs^ args);

		private:
			std::map<Key, bool> m_oPressedKeyMap;
		};

		UWPKeyEventHandler^ keyEventHandler;
		std::map<Key, bool> m_oPressedKeyMap;
	};
}