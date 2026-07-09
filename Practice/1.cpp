#include <iostream>
#include <cmath>

int main()
{
    /*
    int correct = 8;
    int questions = 10;
    double score = correct / (double) questions * 100;

    std::cout << score << "%";

    */

    /*
    std::string name;
    int age;

    std::cout << "What's your age?";
    std::cin >> age;

    std::cout << "What's your name?";
    std::getline(std::cin >> std::ws, name);

    std::cout << "Hello " << name << '\n';
    std::cout << "You are " << age << " years old";
    */
    
    /*
    double x = 3.99;
    double y = 4;
    double z;

    z = std::max(x, y);
    z = std::min(x, y);
    z = pow(2, 4);
    z = sqrt(9);
    z = abs(-3);
    z = round(x);
    z = ceil(x);
    z = floor(x);

    std::cout << z;
    */

    int age;

    std::cout << "Enter your age: ";
    std::cin >> age;

    if ( age >= 100 )
    {
        std::cout << "You are too old to enter this site!";
    }
    else if ( age >= 18 )
    {
        std::cout << "Welcome to the site!";
    }
    else if ( age >= 0 )
    {
        std::cout << "You haven't been born yet!";
    }
    else
    {
        std::cout << "You are not old enough to enter!";
    }

    return 0;
}