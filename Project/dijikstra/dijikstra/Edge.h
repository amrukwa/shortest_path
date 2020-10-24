#pragma once
# include <iostream>

void check_nodes(int v, int w)
{
	if (v == w)
	{
		std::cout << "Duplicate node for an edge.";
		throw std::invalid_argument("Duplicate node for an edge.");
	}
	if (v < 0 || w < 0)
	{
		std::cout << "Node cannot be negative.";
		throw std::invalid_argument("Node cannot be negative.");
	}
}

class Edge
{
private:
	int start; // is a position in vector of Nodes
	int destination; // is a position in vector of Nodes
	double dist;
public:
	Edge() {}
	~Edge() {}
	Edge(int v, int w, double d)
	{
		try 
		{
			start = v;
			destination = w;
			dist = d;
			check_nodes(v, w);
			if (d == 0)
			{
				std::cout << "The edge length cannot be 0.";
				throw std::invalid_argument("The edge length cannot be 0.");
			}
			if (d < 0) {throw 1;}
		}
		catch (int) {dist = -d;}
	}
};