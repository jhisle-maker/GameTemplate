#pragma once

//START FORWARD DECL
namespace GT { class ISamplerState; }
//END FORWAR DECL

namespace GT
{
	class ISamplerStatesService
	{
	public:
		ISamplerStatesService() {};
		virtual ~ISamplerStatesService() {};

	public:
		virtual void InitSamplerStates() = 0;

		virtual const ISamplerState& GetLinearSamplerState() const = 0;
		virtual const ISamplerState& GetAnisotropicSamplerState() const = 0;
	};
}
