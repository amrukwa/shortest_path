#pragma once
# include <fstream>

std::ifstream validate_directory();

class NoDirectory : public std::exception
{
public:
	void get_dir(std::ifstream& ifile)
	{
		std::cout << "No such file." << std::endl;
		ifile = validate_directory();
	}
};

std::ifstream ask_for_directory()
{
	std::string dir;
	std::ifstream ifile;
	std::cout << "Please specify the directory of the file with the cities." << std::endl;
	std::cin >> dir;
	ifile.open(dir);
	if (!ifile) { throw NoDirectory(); }
	return ifile;
}

std::ifstream validate_directory()
{
	std::ifstream ifile;
	try { ifile = ask_for_directory(); }
	catch (NoDirectory err) { err.get_dir(ifile); }
	return ifile;
}

std::ifstream load_from_current()
{
	std::ifstream ifile;
	ifile.open("data.txt");
	if (!ifile) { throw NoDirectory(); }
	return ifile;
}

void finish()
{
	std::cout << "Press any key to continue..." << std::endl;
	char c = getchar();
	if (c == '\n') { c = getchar(); }
}