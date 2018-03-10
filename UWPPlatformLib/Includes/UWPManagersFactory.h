#pragma once
#include "pch.h"
#include "IManagersFactory.h"
#include <memory>
#include <agile.h>
#include <d3d11_3.h>

//START FORWARD DECLS
namespace GT { class IGraphicManager; }
namespace GT { class IContentManager; }
namespace GT { class IInputManager; }
namespace GT { class IGraphicContext; }
namespace GT { class IGraphicDevice; }
//END FORWARD DECLS

namespace GT
{



	class UWPManagersFactory : public IManagersFactory
	{
	public:
		UWPManagersFactory(Platform::Agile<Windows::UI::Core::CoreWindow> i_oWindow);
		virtual ~UWPManagersFactory();

	public:
		void CreateManagers
		(
			std::unique_ptr<IGraphicManager>& o_oGraphicManager,
			std::unique_ptr<IContentManager>& o_poContentManager,
			std::unique_ptr<IInputManager>& o_poInputManager
		) const;

	private:
		UWPManagersFactory(const UWPManagersFactory& i_oOther) = delete;
		UWPManagersFactory& operator=(const UWPManagersFactory& i_oOther) = delete;

	private:
		Platform::Agile<Windows::UI::Core::CoreWindow> m_oAgileWindow;
	};
}