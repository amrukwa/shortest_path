# include <iostream>

template <class T>
class calculator 
{
private:
	T a, b;
public:
	calculator(T x, T y)
	{
		a = x;
		b = y;
	}
	~calculator(){}
	T add() { return a + b; }
	T subtract() { return a - b; }
	T multiply() { return a * b; }
	T divide() 
	{ 
		if (b == 0) { return 0; }
		return a / b;
	}
	void present_results()
	{
		std::cout << "Addition: " << add() << std::endl;
		std::cout << "Subtraction: " << subtract() << std::endl;
		std::cout << "Multiplication: " << multiply() << std::endl;
		std::cout << "Division: " << divide() << std::endl;
	}
};

int main()
{
	calculator<int> calc_int(10, 5);
	std::cout << "Results for integer calculator:" << std::endl;
	calc_int.present_results();
	calculator<float> calc_float(10.5, 2.1);
	std::cout << "Results for float calculator:" << std::endl;
	calc_float.present_results();
	return 0;
}