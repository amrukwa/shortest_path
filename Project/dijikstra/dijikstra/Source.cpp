#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# include "Graph.h"
# include "file_handling.h"

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	std::ifstream datafile;
	if (argc == 1)
	{
		try { load_from_current(datafile); }
		catch (NoDirectory err) { err.terminate(); }
	}
	for (int i = 1; i < argc; i++) {use_commands(argv[i], datafile);}
	Graph graph(datafile);
	datafile.close();
	finish();
	return 0;
}