#pragma once

#include "IContentManager.h"
#include "Common.h"
#include <memory>
#include <unordered_map>

//START FORWARD DECLS
namespace GT { class IFileLoaderService; }
namespace GT { class IShaderLoaderService; }
namespace GT { class ITextureLoaderService; }
namespace GT { class IFile; }
namespace GT { class ITexture; }
namespace GT { class IVertexShader; }
namespace GT { class IPixelShader; }
//END FORWARD DECLS

namespace GT
{
	class ContentManager : public IContentManager
	{
	public:
		ContentManager
		(
			IFileLoaderService* i_poFileLoaderService,
			IShaderLoaderService* i_poShaderLoaderService,
			ITextureLoaderService* i_poTextureLoaderService
		);

		~ContentManager();

	public:
		std::unique_ptr<IFile> LoadFile(const std::string& i_ofilePath) const;
		ITexture& LoadTexture(const std::string& i_oTexturePath);
		IVertexShader& LoadVertexShader(const std::string& i_oShaderPath, const VertexDeclaration& i_oVertexDeclaration);
		IPixelShader& LoadPixelShader(const std::string& i_oShaderPath);

	private:
		ContentManager(const ContentManager& i_oOther) = delete;
		ContentManager& operator=(const ContentManager& i_oOther) = delete;

	private:
		std::unique_ptr<IFileLoaderService> m_poFileLoaderService;
		std::unique_ptr<IShaderLoaderService> m_poShaderLoaderService;
		std::unique_ptr<ITextureLoaderService> m_poTextureLoaderService;

	private:
		std::unordered_map<ObjectId, std::unique_ptr<ITexture>, ObjectId> m_oTextureCache;
		std::unordered_map<ObjectId, std::unique_ptr<IVertexShader>, ObjectId> m_oVertexShaderCache;
		std::unordered_map<ObjectId, std::unique_ptr<IPixelShader>, ObjectId> m_oPixelShaderCache;
	};
}
