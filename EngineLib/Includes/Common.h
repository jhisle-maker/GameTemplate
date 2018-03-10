#pragma once
#include <cassert>
#include <string>
#include <Logger.h>

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
		ObjectId() : std::string() {};
		ObjectId(const char* i_szId) : std::string(i_szId) {};
		ObjectId(const std::string& i_oString) : ObjectId(i_oString.data()) {}
		ObjectId(const ObjectId& i_oOther) : std::string(i_oOther.data()) {}

	public:
		size_t operator()(const ObjectId& key) const
		{
			return std::hash<std::string>()(key);
		}
	};
}

