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
	Handle_Commands hc(argc, argv);
	hc.handle_commands(datafile);
	Graph graph(datafile);
	datafile.close();
	graph.dijikstra();
	graph.show_path();
	hc.finish();
	return 0;
}