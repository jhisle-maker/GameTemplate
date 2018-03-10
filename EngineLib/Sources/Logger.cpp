#include "Logger.h"

namespace GT
{
	const ILogger* Logger::m_oLogger = nullptr;

	Logger::Logger()
	{
		//Nothing to do here
	}

	Logger::~Logger()
	{
		//Nothing to do here
	}

	void Logger::Init(const ILogger& i_oLoggerInstance)
	{
		m_oLogger = &i_oLoggerInstance;
	}

	void Logger::Log(const std::string& i_oMessage, const LogSeverity i_eSeverity, const uint8_t i_uiLevel)
	{
		m_oLogger->Log(i_oMessage, i_eSeverity, i_uiLevel);
	}
}