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

		TEST_METHOD(Test_is_name)
		{
			Node node("trial");
			Assert::IsTrue(node.is_name("trial"));
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
		TEST_METHOD(Test_if_node)
		{
			Graph graph;
			graph.add_node("0");
			graph.add_node("1");
			graph.add_node("2");
			for (int i = 0; i < 3; i++)
			{
				std::string s = std::to_string(i);
				Assert::AreEqual(s, graph.nodes[i].name);
			}
		}
		TEST_METHOD(Test_if_edge)
		{
			Graph graph;
			int* starts = (int*)malloc(sizeof(int) * 2);
			starts[0] = 0;
			starts[1] = 2;
			int* ends = (int*)malloc(sizeof(int) * 2);
			ends[0] = 1;
			ends[1] = 0;
			double* dists = (double*)malloc(sizeof(double) * 2);
			dists[0] = 2.0;
			dists[1] = 3.0;
			graph.add_node("zero");
			graph.add_node("one");
			graph.add_node("two");
			graph.add_edge("zero", "one", 2.0);
			graph.add_edge("two", "zero", 3.0);
			for (int i = 0; i < 2; i++)
			{
				Assert::AreEqual(starts[i], graph.edges[i].start);
				Assert::AreEqual(ends[i], graph.edges[i].destination);
				Assert::AreEqual(dists[i], graph.edges[i].dist);
			}
			free(starts);
			free(ends);
			free(dists);
		}

		TEST_METHOD(Test_from_one_line_new)
		{
			Graph graph;
		}
	};

	TEST_CLASS(testDijikstra)
	{
	public:
	};
}
