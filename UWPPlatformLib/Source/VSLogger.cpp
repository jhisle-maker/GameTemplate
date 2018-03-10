#include "VSLogger.h"
#include <Windows.h>

namespace GT
{
	VSLogger::VSLogger()
	{
		//Nothing to do here
	}

	VSLogger::~VSLogger()
	{
		//Nothing to do here
	}

	void VSLogger::Log(const std::string& i_oMessage, const LogSeverity i_eSeverity, const uint8_t i_uiLevel) const
	{
		OutputDebugStringA((std::string("GTLOG:: ") + i_oMessage).c_str());
	}
}