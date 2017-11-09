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
		void LoadShaders();

		inline const IPixelShader& GetPositionColorPS() const { return *i_poPositionColorPS; }
		inline const IVertexShader& GetPositionColorVS() const { return *i_poPositionColorVS; }
		inline const IPixelShader& GetPositionColorTexturePS() const { return *i_poPositionColorTexturePS; }
		inline const IVertexShader& GetPositionColorTextureVS() const { return *i_poPositionColorTextureVS; }

	private:
		const IShaderLoaderService& m_oShaderLoaderService;

		std::unique_ptr<IPixelShader> i_poPositionColorPS;
		std::unique_ptr<IVertexShader> i_poPositionColorVS;
		std::unique_ptr<IPixelShader> i_poPositionColorTexturePS;
		std::unique_ptr<IVertexShader> i_poPositionColorTextureVS;
	};
}