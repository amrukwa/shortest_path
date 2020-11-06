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

	void visit() {visited = true;}

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
	friend class Pair;
	friend class Graph;
};

class Pair
{
private:
	int index = 0;
	double cur_dist = 0;
public:
	Pair(){}
	Pair(const Node& node, int idx)
	{
		index = idx;
		cur_dist = node.dist;
	}
	~Pair() {}
	friend bool operator> (const Pair& a, const Pair& b);
	friend bool operator< (const Pair& a, const Pair& b);
	friend class Graph;
};

bool operator> (const Pair& a, const Pair& b) { return a.cur_dist > b.cur_dist; }
bool operator< (const Pair& a, const Pair& b) { return a.cur_dist < b.cur_dist; }
