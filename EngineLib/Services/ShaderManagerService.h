#pragma once

#include "IShaderManagerService.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\IVertexShader.h"

#include <memory>

namespace GT
{
	class ShaderManagerService : public IShaderManagerService
	{
	public:
		ShaderManagerService(const IShaderLoaderService& i_oShaderLoaderService);
		~ShaderManagerService();

	public:
		void LoadShaders(const std::map<std::string, std::string>& i_oShaderFileRegistry);

		inline const IPixelShader& GetPositionColorPS() const { return *m_poPositionColorPS; }
		inline const IVertexShader& GetPositionColorVS() const { return *m_poPositionColorVS; }
		inline const IPixelShader& GetPositionColorTexturePS() const { return *m_poPositionColorTexturePS; }
		inline const IVertexShader& GetPositionColorTextureVS() const { return *m_poPositionColorTextureVS; }

	private:
		const IShaderLoaderService& m_oShaderLoaderService;

		std::unique_ptr<IPixelShader> m_poPositionColorPS;
		std::unique_ptr<IVertexShader> m_poPositionColorVS;
		std::unique_ptr<IPixelShader> m_poPositionColorTexturePS;
		std::unique_ptr<IVertexShader> m_poPositionColorTextureVS;
	};
}