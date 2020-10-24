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
	Node(std::string n)
	{
		name = n;
	}
	~Node(){}

	void visit()
	{
	}
};

