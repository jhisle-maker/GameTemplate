#pragma once

#include <string>

namespace GT
{
	enum LogSeverity
	{
		eInfo,
		eWarning,
		eError
	};

	class ILogger
	{
	public:
		ILogger() {}
		virtual ~ILogger() {}

	public:
		virtual void Log(const std::string& i_oMessage, const LogSeverity i_eSeverity = LogSeverity::eInfo, const uint8_t i_uiLevel = 0u) const = 0;
	};
}
