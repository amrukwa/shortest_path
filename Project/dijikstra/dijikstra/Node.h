#pragma once
# include <iostream>
# include <limits>
# include <string>
# include <vector>
#include <queue> 
# define INF std::numeric_limits<int>::max()

/// this class holds point characteristics:
/// its name, if it was visited, its distance from the beginning of the graph,
/// and the index of the previous point on the graph path.
class Node {
private:
	bool visited = false;
	double dist = INF;
	int previous = -1;

public:
	std::string name;

	/// default constructor of the class object.
	Node() {}

	/// parametrized constructor, setting name of the node.
	Node(std::string n) {name = n;}

	/// copy constructor, copying current data from other node.
	Node(const Node& n)
	{
		visited = n.visited;
		dist = n.dist;
		name = n.name;
		previous = n.previous;
	}

	/// destructor
	~Node(){}

	/// the method checks if the node name is the same as the given string.
	bool is_name(std::string n)
	{
		if (name == n)
		{
			return true;
		}
		return false;
	}

	/// sets this->visited to true.
	void visit() {visited = true;}

	/// checks if the distance from the start improves while going through Node
	/// with index prev and distance d from this object;
	/// if it improves, the distance and previous of the object are improved.
	bool check_prev(int prev, double d) 
	{
		if (d < dist)
		{
			dist=d;
			previous = prev;
			return true;
		}
		return false;
	}
	
	/// friend classes for easier implementation of the algorithm
	friend class Pair;
	friend class Graph;
};

/// this class stores a pair of integer and double
class Pair
{
private:
	int index = 0;
	double cur_dist = 0;
public:
	/// default constructor
	Pair(){}

	/// constructs the object from the node, taking its distance from the start
	/// and index in the vector of nodes.
	Pair(const Node& node, int idx)
	{
		index = idx;
		cur_dist = node.dist;
	}
	
	/// default destructor
	~Pair() {}
	friend bool operator> (const Pair& a, const Pair& b);
	friend bool operator< (const Pair& a, const Pair& b);
	/// friend class for easier implementation of priority queue
	friend class Graph;
};

/// operators comparing cur_dist members of the class instances
bool operator> (const Pair& a, const Pair& b) { return a.cur_dist > b.cur_dist; }
bool operator< (const Pair& a, const Pair& b) { return a.cur_dist < b.cur_dist; }
