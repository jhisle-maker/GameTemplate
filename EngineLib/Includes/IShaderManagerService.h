#pragma once

#include <map>
#include <string>

//START FORWARD DECL
namespace GT
{
	class IPixelShader;
	class IVertexShader;
	class IShaderLoaderService;
	class ShadersRegistryService;
	class ObjectId;
}
//END FORWARD DECL

namespace GT
{
	class IShaderManagerService
	{
	public:
		IShaderManagerService() {}
		virtual ~IShaderManagerService() {}

	public:
		virtual void LoadShaders(const ShadersRegistryService& i_oShadersRegistry) = 0;

		virtual const IPixelShader& GetPixelShader(const ObjectId& i_oObjectId) const = 0;
		virtual const IVertexShader& GetVertexShader(const ObjectId& i_oObjectId) const = 0;
	};
}