#pragma once

namespace Engine
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		void getTestString(char*& outArray) { outArray = "test"; }
	};
}