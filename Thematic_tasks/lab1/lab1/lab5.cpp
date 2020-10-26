#include <exception>
#include <iostream>
#include <string>
#include <array>
#include <fstream>

class By0Division : public std::exception
{

};

class OutOfRange : public std::exception
{

};

class NoFile : public std::exception
{

};

class GoodClass
{
	int i = 0;
	std::array<int, 5> my_storage = { -2, -1, 0, 1, 2 };
public:

	int SecureFunction1()
	{
		for (int i = 0; i < my_storage.size() - 1; i++)
		{
			try
			{
				if (my_storage[i + 1] == 0)
				{
					throw By0Division();
				}
				float result = float(my_storage[i]) / my_storage[i + 1];
				std::cout << result << std::endl; 
			}
			catch (By0Division err)
			{
				std::cout << "Division by 0 would be performed." << std::endl;
			}
		}
		return 0; //if all goes well
	}

	int SecureFunction2()
	{
		for (i = 0; i <= my_storage.size(); i++)
		{
			try 
			{
				if (i >= my_storage.size())
				{
					throw OutOfRange();
				}
				std::cout << my_storage[i] << std::endl;
			}
			catch (OutOfRange err)
			{
				std::cout << "That's the end of the array." << std::endl;
			}
		}
		return 0;
	}

	int SecureFunction3()
	{
		FILE* fp;
		try 
		{
			fopen_s(&fp, "txt.txt", "r");
			if (fp == NULL)
			{
				throw NoFile();
			}
			char* line = NULL;
			size_t len = 0;
			fgets(line, len, fp);
			printf("%s", line);
			fclose(fp);
			if (line)
				free(line);
		}
		catch (NoFile err)
		{
			std::cout << "No file detected." << std::endl;
		}

		return 0;
	}
};


int main()
{
	GoodClass someclass;
	someclass.SecureFunction1();
	someclass.SecureFunction2();
	int i = someclass.SecureFunction3();
	std::cout << "Congrats, you made it!" << std::endl;
}