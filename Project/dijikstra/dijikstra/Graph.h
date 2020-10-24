#pragma once
# include "Edge.h"
# include "Node.h"


class Graph
{
private:
	std::vector <Node> nodes;
	std::vector <Edge> edges;
public:
	Graph(){}
	~Graph(){}

	Graph(std::ifstream& datafile)
	{
	}

	void from_one_set(std::string start, std::string aim, double d)
	{
		int find_start = find_and_fill_node(start);
		int find_aim = find_and_fill_node(aim);
		Edge someEdge(find_start, find_aim, d);
		edges.push_back(someEdge);
	}

	int find_where_node(std::string name)
	{
		std::vector<Node>::iterator it;
		int i = -1; // this way we will know there is none such node
		int pos = 0;
		for (it = nodes.begin(); it != nodes.end(); it++) 
		{
			if (it->is_name(name))
			{
				i = pos;
				break;
			}
			pos += 1;
		}
		return i;
	}
	int find_and_fill_node(std::string name)
	{
		int i = find_where_node(name);
		if (i == -1)
		{
			add_node(name);
			i = find_where_node(name);
		}
		return i;
	}
	void add_node(std::string name)
	{
		Node someNode(name);
		nodes.push_back(someNode);
	}
};