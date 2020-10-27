#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# include "Graph.h"

std::string ask_for_directory()
{
	std::ifstream ifile;
	std::cout << "Please specify the directory of the file with the cities." << std::endl;
	std::string dir;
	std::cin >> dir;
	try {
		ifile.open(dir);
		if (!ifile){throw 1;}
	}
	catch(int i)
	{
		std::cout << "No such file." << std::endl;
		dir = ask_for_directory();
	}
	return dir;
}

std::ifstream load_from_current()
{
	std::ifstream ifile;
	ifile.open("data.txt");
	return ifile;
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
	std::ifstream datafile = load_from_current();
	if (!datafile) 
	{
		std::string dir = ask_for_directory();
		datafile.open(dir);
	}
	Graph graph(datafile);
	datafile.close();
	finish();
	return 0;
}