#pragma once

#include "ILogger.h"
#include <memory>

namespace GT
{
	class Logger
	{
	private:
		Logger();

	public:
		~Logger();

	public:
		static void Init(const ILogger& i_oLoggerInstance);
		static void Log(const std::string& i_oMessage, const LogSeverity i_eSeverity = LogSeverity::eInfo, const uint8_t i_uiLevel = 0u);

	private:
		static const ILogger* m_oLogger;
	};
}