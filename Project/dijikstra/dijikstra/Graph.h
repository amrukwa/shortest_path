#pragma once
# include "Edge.h"
# include "Node.h"
#include<fstream>

std::vector<bool> check_lines(std::ifstream& datafile)
{
	std::vector<bool> is_for_graph;
	int cur_rows = 0;
	char c;
	while (datafile.get(c))
	{
		if (c == ' ') {cur_rows += 1;}
		else if (c == '\n')
		{
			if (cur_rows == 2) { is_for_graph.push_back(true); }
			else { is_for_graph.push_back(false); }
			cur_rows = 0;
		}
	}
	return is_for_graph;
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
		std::cout << "The map consists of the following cities: " << std::endl;
		std::vector<Node>::iterator it;
		for (it = nodes.begin(); it != nodes.end(); it++)
		{std::cout << it->name << std::endl;}
	}

	int user_choose_node(std::string which_node)
	{ 
		int node;
		std::string n;
		std::cout << "Choose the " << which_node << ":" << std::endl;
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

	void ask_about_line(std::string line)
	{
		std::string st, end;
		double dist;
		std::cout << line << "was provided. Specify the actual edge." << std::endl;
		std::cin >> st >> end >> dist;
		try {if (dist == 0) {throw 1;}}
		catch (int)
		{
			std::cout << "The edge should have positive value. Specify the correct length." << std::endl;
			std::cin >> dist;
		}
		from_one_set(st, end, dist);
	}

	void read_typical_line(std::ifstream& datafile)
	{
		std::string st, end;
		double dist = -1;
		try {
			datafile >> st >> end >> dist;
			if (datafile.fail()) { throw 'f'; }
			else if (dist == 0) { throw 0; }
		}
		catch (int)
		{
			std::cout << st << " " << end << std::endl;
			std::cout << "The edge should have positive value. Specify the correct length." << std::endl;
			std::cin >> dist;
		}
		catch (char)
		{
			std::string trashbox;
			std::cout << st << " " << end << std::endl;
			std::cout << "Invalid edge. Specify the correct length." << std::endl;
			std::cin >> dist;
			datafile.clear();
			datafile >> trashbox;
		}
		from_one_set(st, end, dist);
	}

	void load_data(std::ifstream& datafile, std::vector<bool>& is_for_graph)
	{
		for (int i = 0; i < is_for_graph.size(); i++)
		{
			if (is_for_graph[i]) {read_typical_line(datafile);}
			else if (i == (is_for_graph.size()-1))
			{
				std::string st, end;
				datafile >> st >> end;
				int s = find_where_node(st);
				int e = find_where_node(end);
				if ((s == -1) || (e == -1)) 
				{
					std::cout << "At least one of the nodes doesn't belong to the graph." << std::endl;
					is_for_graph[i] = true;
				}
				else
				{
					start = s;
					ending = e;
				}
			}
			else
			{
				std::string line;
				std::getline(datafile, line);
				ask_about_line(line);
			}
		}
	}

public:
	Graph(){}
	~Graph(){}

	Graph(std::ifstream& datafile)
	{
		std::vector<bool> is_for_graph = check_lines(datafile);
		datafile.clear();
		datafile.seekg(0, std::ios::beg);
		load_data(datafile, is_for_graph);
		if (is_for_graph.back()) {ask_about_path();}
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