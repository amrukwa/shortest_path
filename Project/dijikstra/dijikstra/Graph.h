#pragma once
# include "Edge.h"
# include "Node.h"
#include<fstream>

void check_line(std::ifstream& datafile)
{

}

class Graph
{
private:
	std::vector <Node> nodes;
	std::vector <Edge> edges;
	int ending;
	int start;

	void show_nodes()
	{
		std::cout << "The map consists of the following cities:" << std::endl;
		std::vector<Node>::iterator it;
		for (it = nodes.begin(); it != nodes.end(); it++)
		{std::cout << it->name << std::endl;}
	}

	int user_choose_node(std::string which_node)
	{ 
		int node;
		std::string n;
		std::cout << "Choose the " << which_node << std::endl;
		std::cin >> n;
		try {
			node = find_where_node(n);
			if (node == -1) {throw 1;}
		}
		catch (int)
		{
			std::cout << "No such node. Choose again." << std::endl;
			node = user_choose_node(which_node);
		}
		return node;
	}

	void ask_about_path()
	{
		show_nodes();
		start = user_choose_node("starting node");
		ending = user_choose_node("ending node");
	}

	void load_data(std::ifstream& datafile)
	{
		check_line(datafile);
	}

public:
	Graph(){}
	~Graph(){}

	Graph(std::ifstream& datafile)
	{
		load_data(datafile);
		ask_about_path();
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