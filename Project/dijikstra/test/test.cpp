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
		TEST_METHOD(Test_find_and_fill)
		{
			Graph graph;
			int v0 = graph.find_and_fill_node("v0");
			graph.add_node("v1");
			int v1 = graph.find_and_fill_node("v1");
			Assert::AreEqual(0, v0);
			Assert::AreEqual(1, v1);
		}
		TEST_METHOD(Test_from_one_set_new)
		{
			Graph graph;
			graph.from_one_set("v1", "v0", 2.3);
			std::string v0 = "v0";
			std::string v1 = "v1";
			Assert::AreEqual(v0, graph.nodes[1].name);
			Assert::AreEqual(v1, graph.nodes[0].name);
			Assert::AreEqual(0, graph.edges[0].start);
			Assert::AreEqual(1, graph.edges[0].destination);
			Assert::AreEqual(2.3, graph.edges[0].dist);

		}
		TEST_METHOD(Test_from_one_set_adding)
		{
			Graph graph;
			graph.from_one_set("v0", "v1", 2.3);
			graph.from_one_set("v2", "v0", 3.3);
			std::string v0 = "v0";
			std::string v2 = "v2";
			Assert::AreEqual(v0, graph.nodes[0].name);
			Assert::AreEqual(v2, graph.nodes[2].name);
			Assert::AreEqual(2, graph.edges[1].start);
			Assert::AreEqual(0, graph.edges[1].destination);
			Assert::AreEqual(3.3, graph.edges[1].dist);
		}
	};

	TEST_CLASS(testDijikstra)
	{
	public:
	};
}
