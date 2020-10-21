#include <iostream>
# include <string>

class Person {
	int age;
	std::string name;
public:
	Person() { 
		age = 25;
		name = "unknown";
		std::cout << "Person constructor called." << std::endl; 
	}
	~Person() { std::cout << "Person destructor called." << std::endl; }
};

class Employee {
	int experience;
	std::string position_name;
public:
	Employee() { 
		experience = 0;
		position_name = "unspecified";
		std::cout << "Employee constructor called." << std::endl; }
	~Employee() { std::cout << "Employee destructor called." << std::endl; }
};

class Teacher : public Person, public Employee {
public:
	Teacher() { std::cout << "Teacher constructor called." << std::endl; }
	~Teacher() { std::cout << "Teacher destructor called." << std::endl; }
};

int main()
{
	Teacher some_teacher;
	return 0;
}