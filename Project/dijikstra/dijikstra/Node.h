#pragma once
# include <iostream>
# include <limits>
# include <string>
# include <vector>
#include <queue> 
# define INF std::numeric_limits<int>::max()

class Node {
private:
	bool visited = false;
	double dist = INF;
	int previous = -1;

public:
	std::string name;
	Node(){}
	Node(std::string n) {name = n;}

	Node(const Node& n)
	{
		visited = n.visited;
		dist = n.dist;
		name = n.name;
		previous = n.previous;
	}

	~Node(){}

	bool is_name(std::string n)
	{
		if (name == n)
		{
			return true;
		}
		return false;
	}

	void set_dist(double d) { dist = d; }

	void visit() {visited = true;}

	void check_prev(int prev, double d)
	{
		if (d < dist)
		{
			set_dist(d);
			previous = prev;
		}
	}
	friend class Pair;
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
