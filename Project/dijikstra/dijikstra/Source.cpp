#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# include "Graph.h"

std::ifstream ask_for_directory()
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
		ifile = ask_for_directory();
	}
	return ifile;
}

std::ifstream load_from_current()
{
	std::ifstream ifile;
	ifile.open("data.txt");
	return ifile;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	std::ifstream datafile = load_from_current();
	if (!datafile) {std::ifstream datafile = ask_for_directory();}
	Graph graph(datafile);
	datafile.close();
	system("pause");
	return 0;
}