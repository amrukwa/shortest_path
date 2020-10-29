#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# include "Graph.h"

std::string validate_directory();

class NoDirectory: public std::exception 
{
public:
	void get_dir(std::string& dir)
	{
		std::cout << "No such file." << std::endl;
		dir = validate_directory();
	}
};

std::string ask_for_directory()
{
	std::ifstream ifile;
	std::cout << "Please specify the directory of the file with the cities." << std::endl;
	std::string dir;
	std::cin >> dir;
	ifile.open(dir);
	if (!ifile){throw NoDirectory();}
	return dir;
}

std::string validate_directory()
{
	std::string dir;
	try {dir = ask_for_directory();}
	catch (NoDirectory err) {err.get_dir(dir);}
	return dir;
}

std::string load_from_current()
{
	std::string dir = "data.txt";
	std::ifstream ifile;
	ifile.open(dir);
	if (!ifile) { throw NoDirectory(); }
	return dir;
}

void finish()
{
	std::cout << "Press any key to continue..." << std::endl;
	char c = getchar();
	if (c == '\n') { c = getchar(); }
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	std::string dir;
	try {dir = load_from_current();}
	catch (NoDirectory err){err.get_dir(dir);}
	std::ifstream datafile;
	datafile.open(dir);
	Graph graph(datafile);
	datafile.close();
	finish();
	return 0;
}