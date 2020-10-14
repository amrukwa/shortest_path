# include <iostream>

class Shape 
{
protected:
	double width = 0;
	double height = 0;
public:
	Shape(){}

	Shape(double a, double b)
	{
		width = a;
		height = b;
	}
	virtual void get_area() = 0;
};

class Rectangle : public Shape {
public:
	Rectangle() {}

	Rectangle(double a, double b)
	{
		width = a;
		height = b;
	}

	void get_area()
	{
		double area = width * height;
		std::cout << "The area of rectangle is equal to " << area << std::endl;
	}
};

class Triangle : public Shape {
public:
	Triangle() {}
	Triangle(int a, int b)
	{
		width = a;
		height = b;
	}

	void get_area()
	{
		double area = (width * height) / 2;
		std::cout << "The area of triangle is equal to " << area << std::endl;
	}
};

int main() {
	double w1, h1, w2, h2;
	std::cout << "Type width and height of the triangle:" << std::endl;
	std::cin >> w1 >> h1;

	std::cout << "Type width and height of the rectangle:" << std::endl;
	std::cin >> w2 >> h2;

	Shape* figure1;
	Triangle fig1(w1, h1);
	figure1 = &fig1;
	figure1->get_area();

	Shape* figure2;
	Rectangle fig2(w2, h2);
	figure2 = &fig2;
	figure2->get_area();

	return 0;
}