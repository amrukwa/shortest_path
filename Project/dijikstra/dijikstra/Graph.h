#pragma once
# include "Edge.h"
# include "Node.h"
#include<fstream>

class ZeroEdge : public std::exception
{
public:
	double specify_edge(std::string st, std::string end)
	{
		double dist;
		std::cout << st << " " << end << std::endl << "The edge should have positive value. Specify the correct length." << std::endl;
		std::cin >> dist;
		return dist;
	}
};

class InvalidEdge : public std::exception
{
public:
	double specify_edge(std::string st, std::string end, std::istream& datafile)
	{
		double dist;
		char trashbox;
		std::cout << st << " " << end << std::endl << "Invalid edge. Specify the correct length." << std::endl;
		datafile.clear();
		datafile >> trashbox;
		std::cin >> dist;
		return dist;
	}
};

class InvalidNode : public std::exception {};

class CheckFile
{
private:
	std ::vector<bool> is_for_graph;
public:
	CheckFile() {}
	~CheckFile(){}
	friend class Graph;
	void check_lines(std::ifstream& datafile)
	{
		int cur_rows = 0;
		char c;
		while (datafile.get(c))
		{
			if (c == ' ') { cur_rows += 1; }
			else if (c == '\n')
			{
				if (cur_rows == 2) { is_for_graph.push_back(true); }
				else { is_for_graph.push_back(false); }
				cur_rows = 0;
			}
		}
	}
	std::string get_line(std::ifstream& datafile)
	{
		char c;
		std::string line;
		datafile.get(c);
		if (c != '\n') { datafile.putback(c); }
		std::getline(datafile, line);
		return line;
	}
};

class Graph
{
private:
	std::vector <Node> nodes;
	std::vector <Edge> edges;
	int ending=1;
	int start=0;

	int user_choose_node(std::string which_node)
	{ 
		int node;
		std::string n;
		std::cout << "Choose the " << which_node << ":" << std::endl;
		std::cin >> n;
		node = find_where_node(n);
		if (node == -1) {throw InvalidNode();}
		return node;
	}

	int user_validate_node(std::string which_node)
	{
		int node;
		try {node = user_choose_node(which_node);}
		catch (InvalidNode)
		{
			std::cout << "No such node." << std::endl;
			exit(1);
		}
		return node;
	}

	void ask_about_path()
	{
		show_nodes();
		start = user_validate_node("starting node");
		ending = user_validate_node("ending node");
	}

	double from_three(std::string& st, std::string& end, std::istream& datafile)
	{
		double dist;
		datafile >> st >> end >> dist;
		if (datafile.fail()) {throw InvalidEdge();}
		if (dist == 0) {throw ZeroEdge();}
		return dist;
	}

	void ask_about_line(std::string line)
	{
		std::string st, end;
		double dist;
		std::cout << line << " was provided. Specify the actual edge." << std::endl;
		try {dist = from_three(st, end, std::cin);}
		catch (ZeroEdge err) {dist = err.specify_edge(st, end);}
		catch (InvalidEdge err) { dist = err.specify_edge(st, end, std::cin); }
		from_one_set(st, end, dist);
	}

	void read_typical_line(std::ifstream& datafile)
	{
		std::string st, end;
		double dist;
		try {dist = from_three(st, end, datafile);}
		catch (ZeroEdge err) {dist = err.specify_edge(st, end);}
		catch (InvalidEdge err) {dist = err.specify_edge(st, end, datafile);}
		from_one_set(st, end, dist);
	}

	void read_aim_line(std::ifstream& datafile, std::vector<bool>& is_for_graph)
	{
		std::string st, end;
		datafile >> st >> end;
		int s = find_where_node(st);
		int e = find_where_node(end);
		if ((s == -1) || (e == -1))
		{
			std::cout << "At least one of the trip nodes doesn't belong to the graph." << std::endl;
			is_for_graph.back() = true;
		}
		else
		{
			start = s;
			ending = e;
		}
	}

	void load_data(std::ifstream& datafile, CheckFile& cf)
	{
		for (int i = 0; i < cf.is_for_graph.size(); i++)
		{
			if (cf.is_for_graph[i]) {read_typical_line(datafile);}
			else if (i == (cf.is_for_graph.size() - 1)) { read_aim_line(datafile, cf.is_for_graph); }
			else
			{
				std::string line = cf.get_line(datafile);
				ask_about_line(line);
			}
		}
	}

	void write_path(std::ofstream& out, std::vector<int> path)
	{
		int previous;
		for (std::vector<int>::reverse_iterator cur = path.rbegin(); cur != path.rend(); ++cur) 
		{
			previous = nodes[*cur].previous;
			if (previous == -1) { continue; }
			out << nodes[previous].name << " " << nodes[*cur].name << " " << find_edge_len(previous, *cur) << std::endl;
		}
	}

public:
	Graph(){}
	~Graph(){}

	Graph(std::ifstream& datafile)
	{
		CheckFile cf;
		cf.check_lines(datafile);
		datafile.clear();
		datafile.seekg(0, std::ios::beg);
		load_data(datafile, cf);
		if (cf.is_for_graph.back()) {ask_about_path();}
	}

	void show_nodes()
	{
		std::cout << "The map consists of the following cities: " << std::endl;
		std::vector<Node>::iterator it;
		for (it = nodes.begin(); it != nodes.end(); it++)
		{
			std::cout << it->name << std::endl;
		}
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
	double find_edge_len(int v, int w)
	{
		double e=0;
		for (auto edge : edges)
		{
			if (edge.start == v && edge.destination == w)
			{
				e = edge.dist;
				break;
			}
		}
		return e;
	}
	void add_node(std::string name)
	{
		Node someNode(name);
		nodes.push_back(someNode);
	}
	std::vector<int> extract_path()
	{
		std::vector<int> path;
		int cur = ending;
		path.push_back(cur);
		while (nodes[cur].previous != -1)
		{
			cur = nodes[cur].previous;
			path.push_back(cur);
		}
		return path;
	}
	void show_path()
	{
		if (!nodes[ending].visited) {std::cout << "There is no path." << std::endl;}
		else 
		{
			std::cout << "There is a path!" << std::endl;
			std::cout << nodes[start].name << " " << nodes[ending].name << " " << nodes[ending].dist << std::endl;
			std::vector<int> path = extract_path();
			std::ofstream outfile("path.txt");
			if (!outfile) 
			{
				std::cout << "Failed to create file.";
				exit(1);
			}
			write_path(outfile, path);
			outfile.close();
		}
	}
	void dijikstra()
	{
		std::priority_queue<Pair, std::vector<Pair>, std::greater<std::vector<Pair>::value_type> > q;
		nodes[start].dist = 0;
		q.push(Pair(nodes[start],start));
		while (!q.empty())
		{
			Pair p = q.top();
			q.pop();
			if (nodes[p.index].visited){continue;}
			nodes[p.index].visit();
			if (p.index == ending) { break; }
			for (auto edge : edges)
			{
				if (p.index == edge.start)
				{
					bool to_push = nodes[edge.destination].check_prev(p.index, edge.dist+nodes[p.index].dist);
					if(to_push) { q.push(Pair(nodes[edge.destination], edge.destination)); }
				}
			}
		}
	}
};

