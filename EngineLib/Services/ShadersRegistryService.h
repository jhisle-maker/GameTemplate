#pragma once

#include <vector>
#include <string>
#include "Utils\Common.h"
#include "Graphics\VertexDeclaration.h"

namespace GT { class ObjectId; }

namespace GT
{
	enum ShaderType
	{
		PIXEL,
		VERTEX
	};
		
	struct ShaderDesc
	{
		ObjectId m_oShaderId;
		std::string m_oPath;
		ShaderType m_eShaderType;
		const VertexDeclaration* m_oVertexDeclaration = nullptr;
	};

	class ShadersRegistryService
	{
	public:
		ShadersRegistryService();
		~ShadersRegistryService();

	public:
		inline void AddVertexShader(const ObjectId& i_oShaderId, const std::string& i_ShaderFilePath, const VertexDeclaration& i_oVertexDeclaration)
		{
			m_oShaderRegistryList.push_back(ShaderDesc { i_oShaderId, i_ShaderFilePath, ShaderType::VERTEX, &i_oVertexDeclaration });
		}

		inline void AddPixelShader(const ObjectId& i_oShaderId, const std::string& i_oShaderFilePath)
		{
			m_oShaderRegistryList.push_back(ShaderDesc { i_oShaderId, i_oShaderFilePath, ShaderType::PIXEL, nullptr });
		}
		
		inline const ShaderDesc& GetShaderDesc(const size_t i_uiIndex) const
		{
			return m_oShaderRegistryList.at(i_uiIndex);
		}

		inline const size_t GetSize() const
		{
			return m_oShaderRegistryList.size();
		}

	public:
		std::vector<ShaderDesc> m_oShaderRegistryList;
	};
}