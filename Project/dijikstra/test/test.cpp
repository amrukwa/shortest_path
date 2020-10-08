#include "pch.h"
#include "CppUnitTest.h"
# include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		
		TEST_METHOD(Testfoo)
		{
			Assert::AreEqual(4, foo(2));
		}
	};
}
