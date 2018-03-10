#pragma once

#include <memory>

//START FORWARD DECLS
namespace GT { class IGraphicManager; }
namespace GT { class IContentManager; }
namespace GT { class IInputManager; }
//END FORWARD DECLS

namespace GT
{
	class IManagersFactory
	{
	public:
		IManagersFactory() {}
		virtual ~IManagersFactory() {}

	public:
		virtual void CreateManagers
		(
			std::unique_ptr<IGraphicManager>& o_oGraphicManager,
			std::unique_ptr<IContentManager>& o_poContentManager,
			std::unique_ptr<IInputManager>& o_poInputManager
		) const = 0;
	};
}