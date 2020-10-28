# include <iostream>
# include <fstream>

class ComplexNumber
{
private:
	double real;
	double imaginary;
public:
	ComplexNumber()
	{
		real = 0;
		imaginary = 0;
	}
	ComplexNumber(double r, double i)
	{
		real = r;
		imaginary = i;
	}
	~ComplexNumber(){}
	void from_file()
	{ 
		// I decided to do it simplier as it is possible in such specified problem, therefore I do not use getline() etc.
		std::ifstream datafile;
		datafile.open("complex.txt");
		if (!datafile) {std::cout << "File could not be opened." << std::endl;}
		else
		{
			double r, i;
			char h;
			datafile >> r >> h >> i;
			real = r;
			imaginary = i;
		}
	}
	friend 	void operator<< (std::ostream& out, const ComplexNumber& z);
};

void operator<< (std::ostream& out, const ComplexNumber& z) {out << z.real << "+" << z.imaginary << "i" << std::endl;}

int main()
{
	ComplexNumber z;
	z.from_file();
	std::cout << z;
	return 0;
}