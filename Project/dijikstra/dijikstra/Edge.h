#pragma once
# include <iostream>
#include <exception>

class NegativeEdge : public std::exception {};

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

void check_dist(double d)
{
	if (d == 0) {throw std::string("The edge length cannot be 0/character.");}
	if (d < 0) { throw NegativeEdge(); }
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
			check_dist(d);
		}
		catch (NegativeEdge) {dist = -d;}
		catch(std::string s)
		{ 
			std::cout << s;
			exit(1); 
		}
	}
};
