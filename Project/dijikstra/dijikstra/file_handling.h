#pragma once
# include <fstream>

class NoDirectory : public std::exception
{
public:
	void terminate()
	{
		std::cout << "No such file in chosen directory." << std::endl;
		exit(1);
	}
};

class Handle_Commands
{
private:
	int arg_number;
	char** argvec;

	void give_help()
	{
		std::cout << "By default, the program will try to read 'data.txt' file from current directory." << std::endl;
		std::cout << "Use --help command to get help on the program usage." << std::endl;
		std::cout << "Use --input= command, location and the name of the file to run the program on it: --input=location\\data.txt" << std::endl;
		std::cout << "If something is wrong with the file you specified, you will be given opportunity to fix this." << std::endl;
	}

	void read_dir(char* adress, std::ifstream& ifile)
	{
		ifile.open(adress);
		if (!ifile) { throw NoDirectory(); }
	}

	void load_from_current(std::ifstream& ifile)
	{
		ifile.open("data.txt");
		if (!ifile) { throw NoDirectory(); }
	}

	void use_command(char* p, std::ifstream& datafile)
	{
		if (strncmp(p, "--help", 6) == 0)
		{
			give_help();
			exit(0);
		}
		if (strncmp(p, "--input=", 8) == 0)
		{
			try { read_dir(p + 8, datafile); }
			catch (NoDirectory err) { err.terminate(); }
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
			exit(1);
		}
	}

public:
	Handle_Commands(int argc, char** argv)
	{
		arg_number = argc;
		argvec = argv; // we do not make a copy here, so we won't have to free the memory.
	}
	~Handle_Commands(){}

	void finish()
	{
		std::cout << "Press any key to continue..." << std::endl;
		char c = getchar();
	}

	void handle_commands(std::ifstream& datafile)
	{
		if (arg_number == 1)
		{
			try { load_from_current(datafile); }
			catch (NoDirectory err) { err.terminate(); }
		}
		for (int i = 1; i < arg_number; i++) { use_command(argvec[i], datafile); }
	}
};
