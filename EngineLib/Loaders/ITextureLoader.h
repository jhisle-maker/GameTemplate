#pragma once
#include <memory>
#include <string>

//START FORWARD DECL
namespace GT { class ITexture; }
//END FORWARD DECL

namespace GT
{
	class ITextureLoader
	{
	public:
		ITextureLoader() {}
		~ITextureLoader() {}

	public: 
		virtual std::unique_ptr<ITexture> Load(const std::string& i_oTexturePath) const = 0;
	};
}