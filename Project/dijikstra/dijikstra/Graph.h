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

	int find_where_node(std::string name)
	{}
	void add_node(std::string name)
	{}
	void add_edge(std::string start, std::string aim, double d)
	{}
};