#pragma once

#include "IApiGraphicResourceWrapper.h"

namespace GT
{
	class ISamplerState
	{
	public:
		ISamplerState() {}
		virtual ~ISamplerState() {}

	public:
		virtual const IApiGraphicResourceWrapper& GetApiWrapper() const = 0;
	};
}