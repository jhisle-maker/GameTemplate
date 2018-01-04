#pragma once
#include <cassert>
#include <string>
#include <Logger\Logger.h>

namespace GT
{
#ifdef _DEBUG
	#define GTASSERT(i_bCondition) assert(i_bCondition);
	#define GTASSERTL(i_bCondition, i_szMessage) if (!i_bCondition) { Logger::Log(i_szMessage); } GTASSERT(i_bCondition);

#else 
	#define GTASSERT 
#endif

	class ObjectId : public std::string
	{
	public:
		ObjectId(const char* i_szId) : std::string(i_szId) {};
	};
}

