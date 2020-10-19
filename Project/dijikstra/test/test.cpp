#include "pch.h"
#include "CppUnitTest.h"
#include "dijikstra/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:	
		TEST_METHOD(Testfoo1)
		{
			Assert::AreEqual(4, foo(2));
		}

		TEST_METHOD(Testfoo2)
		{
			Assert::AreEqual(4, foo(3));
		}
	};
}
