#pragma once
# include <iostream>
#include <exception>

/// exception class for raising exceptions when provided edge is negative.
class NegativeEdge : public std::exception {};

/// class holding two integer indices and distance between them
class Edge
{
private:
	int start=0; // is a position in vector of Nodes
	int destination=1; // is a position in vector of Nodes
	double dist=1.0;

	/// checks if provided double d can be used as a distance
	/// prevents the usage of strings and 0.
	void check_dist(double d)
	{
		if (d == 0) { throw std::string("The edge length cannot be 0/character."); }
		if (d < 0) { throw NegativeEdge(); }
	}

	/// checks provided indices
	/// prevents creating loops or edges between negative indices
	/// as negative indices are reserved for undefined previous points in the Graph class.
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
public:
	/// default constructor
	Edge() {}

	/// default destructor
	~Edge() {}

	/// constructor checking correctness of edge and node indices
	/// the catch for the incorrect values terminates the program
	/// the programmer should check the values before calling the constructor
	/// and prevent the user from creating invalid edge
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
	
	/// copy constructor
	Edge(const Edge& e)
	{
		start = e.start;
		destination = e.destination;
		dist = e.dist;
	}

	/// friend class for algorithm operations
	friend class Graph;
};
