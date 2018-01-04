#pragma once

#include "Utils\Common.h"
#include "IShaderManagerService.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\IVertexShader.h"

#include <memory>

//START FORWARD DECL
namespace GT { class ShadersRegistryService; }
//END FORWARD DEC

namespace GT
{
	class ShaderManagerService : public IShaderManagerService
	{
	public:
		ShaderManagerService(const IShaderLoaderService& i_oShaderLoaderService);
		~ShaderManagerService();

	public:
		void LoadShaders(const ShadersRegistryService& i_oShaderRegistry);
		//void ReleaseShaders(const ShadersRegistryService& i_oShaderRegistry);

		inline const IPixelShader& GetPixelShader(const ObjectId& i_oObjectId) const { return *(m_oPixelShaderMap.at(i_oObjectId)); }
		inline const IVertexShader& GetVertexShader(const ObjectId& i_oObjectId) const { return *(m_oVertexShaderMap.at(i_oObjectId)); }
		
	private:
		const IShaderLoaderService& m_oShaderLoaderService;

		std::map<ObjectId, std::unique_ptr<IPixelShader>> m_oPixelShaderMap;
		std::map<ObjectId, std::unique_ptr<IVertexShader>> m_oVertexShaderMap;
	};
}