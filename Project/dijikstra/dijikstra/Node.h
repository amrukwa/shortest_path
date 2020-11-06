#pragma once
# include <iostream>
# include <limits>
# include <string>
# include <vector>
#include <queue> 
# define INF std::numeric_limits<int>::max()

class Node {
// this class holds point characteristics:
// its name, if it was visited, its distance from the beginning of the graph,
// and the index of the previous point on the graph path.
private:
	bool visited = false;
	double dist = INF;
	int previous = -1;

public:
	std::string name;
	Node() {} 		// default constructor of the class object.
	Node(std::string n) 
	{
		// parametrized constructor, setting name of the node.
		name = n;
	}

	Node(const Node& n)
	// copy constructor, copying current data from other node.
	{
		visited = n.visited;
		dist = n.dist;
		name = n.name;
		previous = n.previous;
	}

	~Node(){} // destructor

	bool is_name(std::string n)
	// the method checks if the node name is the same as the given string.
	{
		if (name == n)
		{
			return true;
		}
		return false;
	}

	void visit() 
	// sets this->visited to true.
	{visited = true;}

	bool check_prev(int prev, double d) 
	// checks if the distance from the start improves while going through Node
	// with index prev and distance d from this object
	// if it improves, the distance and previous of the object are improved.
	{
		if (d < dist)
		{
			dist=d;
			previous = prev;
			return true;
		}
		return false;
	}
	// friend classes for easier implementation of the algorithm
	friend class Pair;
	friend class Graph;
};

class Pair
{
// this class stores a pair of integer and index
private:
	int index = 0;
	double cur_dist = 0;
public:
	Pair(){} // default constructor
	Pair(const Node& node, int idx)
	// constructs the object from the node, taking its distance from the start
	// and index in the vector of nodes.
	{
		index = idx;
		cur_dist = node.dist;
	}
	~Pair() {} // default destructor
	friend bool operator> (const Pair& a, const Pair& b);
	friend bool operator< (const Pair& a, const Pair& b);
	// friend class for easier implementation of priority queue
	friend class Graph;
};

// operators comparing cur_dist members of the class instances
bool operator> (const Pair& a, const Pair& b) { return a.cur_dist > b.cur_dist; }
bool operator< (const Pair& a, const Pair& b) { return a.cur_dist < b.cur_dist; }
