#include "ContentManager.h"

#include "IFileLoaderService.h"
#include "IShaderLoaderService.h"
#include "ITextureLoaderService.h"
#include "IFile.h"
#include "ITexture.h"
#include "IVertexShader.h"
#include "IPixelShader.h"

namespace GT
{
	ContentManager::ContentManager
	(
		IFileLoaderService* i_poFileLoaderService,
		IShaderLoaderService* i_poShaderLoaderService,
		ITextureLoaderService* i_poTextureLoaderService
	)
		: m_poFileLoaderService(i_poFileLoaderService)
		, m_poShaderLoaderService(i_poShaderLoaderService)
		, m_poTextureLoaderService(i_poTextureLoaderService)
	{
		//Nothing to do here
	}

	ContentManager::~ContentManager()
	{
		//Nothing to do here
	}

	std::unique_ptr<IFile> ContentManager::LoadFile(const std::string& i_oFilePath) const
	{
		return m_poFileLoaderService->Load(i_oFilePath);
	}

	ITexture& ContentManager::LoadTexture(const std::string& i_oTexturePath)
	{
		auto it = m_oTextureCache.find(i_oTexturePath);
		if (it == m_oTextureCache.cend())
		{
			std::unique_ptr<ITexture> poTexture = m_poTextureLoaderService->Load(i_oTexturePath);
			ITexture* poTextureRaw = poTexture.get();

			m_oTextureCache[ObjectId(i_oTexturePath)] = std::move(poTexture);

			return *poTextureRaw;
		}
		
		return *(it->second);
	}

	IVertexShader& ContentManager::LoadVertexShader(const std::string& i_oShaderPath, const VertexDeclaration& i_oVertexDeclaration)
	{
		auto it = m_oVertexShaderCache.find(i_oShaderPath);
		if (it == m_oVertexShaderCache.cend())
		{
			std::unique_ptr<IVertexShader> poShader = m_poShaderLoaderService->LoadVertexShader(i_oShaderPath, i_oVertexDeclaration);
			IVertexShader* poShaderRaw = poShader.get();

			m_oVertexShaderCache[ObjectId(i_oShaderPath)] = std::move(poShader);

			return *poShaderRaw;
		}
		return *(it->second);
	}

	IPixelShader& ContentManager::LoadPixelShader(const std::string& i_oShaderPath)
	{
		auto it = m_oPixelShaderCache.find(i_oShaderPath);
		if (it == m_oPixelShaderCache.cend())
		{
			std::unique_ptr<IPixelShader> poShader = m_poShaderLoaderService->LoadPixelShader(i_oShaderPath);
			IPixelShader* poShaderRaw = poShader.get();

			m_oPixelShaderCache[ObjectId(i_oShaderPath)] = std::move(poShader);

			return *poShaderRaw;
		}
		return *(it->second);
	}
}