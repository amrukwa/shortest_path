#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# include "Graph.h"
# include "file_handling.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	std::ifstream datafile;
	try {datafile = load_from_current();}
	catch (NoDirectory err){err.get_dir(datafile);}
	Graph graph(datafile);
	datafile.close();
	finish();
	return 0;
}