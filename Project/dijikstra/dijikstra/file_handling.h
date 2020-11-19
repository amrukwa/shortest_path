#pragma once
# include <fstream>

/// class for raising exception when the file cannot be found
/// as calling the program from the console will take the same amount of time
/// as would asking the user about the correct one again, 
/// it terminates the program with an appropriate message
class NoDirectory : public std::exception
{
public:
	void terminate()
	{
		std::cout << "No such file in chosen directory." << std::endl;
		exit(1);
	}
};

/// class for handling the arguments called with the program
class Handle_Commands
{
private:
	int arg_number;
	char** argvec;

	/// prints the help from the help file to the console
	void give_help()
	{
		std::ifstream ifile;
		ifile.open("help.txt");
		std::string str;
		if (!ifile) { throw NoDirectory(); }
		while (std::getline(ifile, str)) {std::cout << str << std::endl;}
		ifile.close();
	}

	/// opens and checks the existence of the directory (address) through ifile
	void read_dir(char* adress, std::ifstream& ifile)
	{
		ifile.open(adress);
		if (!ifile) { throw NoDirectory(); }
	}

	/// tries to load the datafile from the directory where the program is running
	void load_from_current(std::ifstream& ifile)
	{
		ifile.open("data.txt");
		if (!ifile) { throw NoDirectory(); }
	}

	/// method handling commands specified with the program call
	void use_command(char* p, std::ifstream& datafile)
	{
		if (strncmp(p, "--help", 6) == 0)
		{
			try { give_help(); }
			catch (NoDirectory) { std::cout << "Help file could not be found."; }
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
	/// constructor expected to use default main arguments
	Handle_Commands(int argc, char** argv)
	{
		arg_number = argc;
		argvec = argv; // we do not make a copy here, so we won't have to free the memory.
	}

	/// destructor
	~Handle_Commands(){}

	/// simple implementation of "system("pause")", because it is against the standard
	void finish()
	{
		std::cout << "Press any key to continue..." << std::endl;
		char c = getchar();
	}

	/// method handling all program calls, including the default with no arguments
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
