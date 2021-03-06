#pragma once
# include "Edge.h"
# include "Node.h"
#include<fstream>

/// as mentioned in class Edge, the programmer is responsible for ensuring correct edges
/// I handle the error of 0 edge ength by asking the user to specify it again.
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

/// used (in this implementation) for reading from file. 
/// If the invalid edge is provided through the command line, program terminates.
/// in case of encountering characters instead of double for edge length, user is asked to provide the length
/// the file status is cleared and the encountered invalid value is omitted from further reading.
class InvalidEdge : public std::exception
{
public:
	double specify_edge(std::string st, std::string end, std::istream& datafile)
	{
		double dist;
		std::string trashbox;
		std::cout << st << " " << end << std::endl << "Invalid edge. Specify the correct length." << std::endl;
		datafile.clear();
		datafile >> trashbox;
		std::cin >> dist;
		return dist;
	}
};

/// class of which instance I will throw when user specifies the node that does not occur in the graph.
class InvalidNode : public std::exception {};

/// class to check if the file's lines can be directly transformed into the graph
class CheckFile
{
private:
	std ::vector<bool> is_for_graph;
public:
	/// default constructor
	CheckFile() {}

	/// destructor
	~CheckFile(){}

	/// friend class to access is_for_graph
	friend class Graph;

	/// this method checks the lines of the datafile and sets the appropriate value at the corresponding index of is_for_graph
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

	/// this method gets the next line from the file, even with trailing enter after previous reading type, and returns it for further usage
	///(some of the data is read with >> operator, some with std::getline, so it is necessary)
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

/// class containing the information about the graph, its nodes and edges, as well as its start and end
class Graph
{
private:
	std::vector <Node> nodes;
	std::vector <Edge> edges;
	int ending=1;
	int start=0;

	/// general method to ask user to specify the chosen node (start/end in this case), 
	/// which_node makes clear what is the user being asked for
	/// if the node name is specified correctly, returns applicable index, otherwise raises an exception
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

	/// asks user to specify start and end of the path after showing possible nodes
	void ask_about_path()
	{
		show_nodes();
		start = user_choose_node("starting node");
		ending = user_choose_node("ending node");
	}

	/// loads and checks if the edge can be created with use of three consecutive informations from the datafile
	double from_three(std::string& st, std::string& end, std::istream& datafile)
	{
		double dist;
		datafile >> st >> end >> dist;
		if (datafile.fail()) {throw InvalidEdge();}
		if (dist == 0) {throw ZeroEdge();}
		return dist;
	}

	/// shows the line to the user and asks them to specify the correct connection
	/// should get two strings (start and end), as well as one double
	/// if the input is incorrect, raises an exception terminating the program.
	void ask_about_line(std::string line)
	{
		std::string st, end;
		double dist;
		std::cout << line << " was provided. Specify the actual edge." << std::endl;
		try {dist = from_three(st, end, std::cin);}
		catch (ZeroEdge err) {dist = err.specify_edge(st, end);}
		catch (InvalidEdge err) { dist = err.specify_edge(st, end, std::cin); }
		if (dist == 0){ throw(InvalidEdge()); }
		from_one_set(st, end, dist);
	}

	/// reads correctly written line (or expected to be such - the program does not know yet if edge could poossibly be character or 0)
	/// if it really is correct, the data is loaded into the graph (edge and nodes)
	/// if it is not, the user is asked to specify the correct edge length.
	/// if user did not correct the length, raises an exception to terminate the program.
	void read_typical_line(std::ifstream& datafile)
	{
		std::string st, end;
		double dist;
		try {dist = from_three(st, end, datafile);}
		catch (ZeroEdge err) {dist = err.specify_edge(st, end);}
		catch (InvalidEdge err) {dist = err.specify_edge(st, end, datafile);}
		if (dist == 0) { throw(InvalidEdge()); }
		from_one_set(st, end, dist);
	}

	/// tries to read the aim line (at this point expects it to be without the specified edge)
	/// if the specified nodes are not found in the graph, changes the value of is_for_graph for the last line to signal the need for asking the user
	/// otherwise simply sets start and end of the graph
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

	/// loads the data from the datafile
	/// if the line is marked as incorrect, the user is asked to correct it
	/// if user improvements are not correct, the inner methods raise exceptions
	/// loads the start and end if possible as well
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

	/// saves the path to the specified file
	/// as the path vector is written backwards, the iterating must be done backwards as well
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
	/// default constructor
	Graph(){}

	/// default destructor
	~Graph(){}

	/// loads to the Graph from the specified datafile, possibly asks the user for corrections
	/// inner methods throw errors if the file could not be corrected in case of typos
	void from_file(std::ifstream& datafile)
	{
		CheckFile cf;
		cf.check_lines(datafile);
		datafile.clear();
		datafile.seekg(0, std::ios::beg);
		load_data(datafile, cf);
		if (cf.is_for_graph.back()) { ask_about_path(); }
	}

	/// shows all the nodes in the graph to the user
	void show_nodes()
	{
		std::cout << "The map consists of the following cities: " << std::endl;
		std::vector<Node>::iterator it;
		for (it = nodes.begin(); it != nodes.end(); it++)
		{
			std::cout << it->name << std::endl;
		}
	}
	
	/// creates an edge from the specified triplet
	/// if the nodes do not exist yet, they are created as well.
	void from_one_set(std::string start, std::string aim, double d)
	{
		int find_start = find_and_fill_node(start);
		int find_aim = find_and_fill_node(aim);
		Edge someEdge(find_start, find_aim, d);
		edges.push_back(someEdge);
	}

	/// finds the index of the node with the given name in the nodes vector and returns it
	/// if the node could not be found, returns -1
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
	
	/// finds the node and returns its index
	/// if the node is not in the vector, creates it and appends it to the vector, returning the new index
	int find_and_fill_node(std::string name)
	{
		int i = find_where_node(name);
		if (i == -1)
		{
			i = size(nodes);
			add_node(name);
		}
		return i;
	}
	
	/// returns the length of the edge between specified points (indices of nodes)
	/// if there is no edge, returns 0
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
	
	/// adds node with given name
	void add_node(std::string name)
	{
		Node someNode(name);
		nodes.push_back(someNode);
	}

	/// finds backward path from the "previous" members of Node objects
	/// and returns it
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
	
	/// if the end point is not visited, shows that there is no path
	/// otherwise shows that the path exists and saves it to the file
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
	
	/// runs the dijkstra algorithm for the specified graph
	void dijkstra()
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
