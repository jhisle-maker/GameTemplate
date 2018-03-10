#pragma once

#include "ILogger.h"

namespace GT
{
	class VSLogger : public ILogger
	{
	public:
		VSLogger();
		virtual ~VSLogger();

	private:
		VSLogger(const VSLogger& i_oOther) {};
		VSLogger& operator= (const VSLogger& i_oOther) {};

	public:
		void Log(const std::string& i_oMessage, const LogSeverity i_eSeverity = LogSeverity::eInfo, const uint8_t i_uiLevel = 0u) const;
	};
}