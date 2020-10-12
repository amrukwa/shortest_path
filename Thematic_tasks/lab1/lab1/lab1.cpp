# include <string>
#include <iostream>

class Drink {
public:
    int calories=0;
    int sugar=0;

    Drink()
    {
        std::cout << "This is a default constructor." << std::endl;
    }

    Drink(int cal, int sweet) {
        calories = cal;
        sugar = sweet;
        std::cout << "This is a parametrized constructor." << std::endl;
    }

    void describe()
    {
        std::cout << "Your beverage has " << calories << " cals including " << sugar << " sugar." << std::endl;
    }
};

class Juice : public Drink {
public:
    std::string flavour;

    Juice()
    {
        flavour = "none";
        std::cout << "This is a derived class default constructor." << std::endl;
    }

    Juice(std::string flavor, int cal, int sweet)
    {
        calories = cal;
        sugar = sweet;
        flavour = flavor;
        std::cout << "This is a derived class parametrized constructor." << std::endl;
    }


};

int main()
{
    Drink Beverage;
    Drink beverage(1, 1);
    std::cout << "Juices:" << std::endl;
    Juice SomeJuice;
    Juice OrangeJuice("sweet", 1, 1);
    OrangeJuice.describe();
    return 0;
}
