#include "pch.h"
#include "CppUnitTest.h"
#define private public // only for the test purposes, I know it is a bad practice
#include "dijikstra/Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_components
{
	TEST_CLASS(testNode)
	{
	public:	
		TEST_METHOD(TestINF)
		{
			// I check if the value chosen randomly is always smaller than infinity.
			Assert::IsTrue(RAND_MAX < INF);
		}

		TEST_METHOD(Test_if_unvisited)
		{
			Node node;
			Assert::IsFalse(node.visited);
		}
	};

	TEST_CLASS(testEdge)
	{
	public:
		TEST_METHOD(Test_if_nonnegative)
		{
			Edge edge(1, 0, -5);
			Assert::AreEqual(5.0, edge.dist);
		}
	};
}

namespace test_graph
{
	TEST_CLASS(testGraph)
	{
	public:
	};

	TEST_CLASS(testDijikstra)
	{
	public:
	};
}
