#include <iostream>

// this code is answer to a quiz on learncpp.com

// this function askes for 3 number values and then prints them in sequantial order
int main()
{
    std::cout << "enter 3 numbers:";
    int x1{}, x2{}, x3{};
    std::cin >> x1 >> x2 >> x3;
    std::cout << "you have entered;" << x1 << ", " << x2 << " and " << x3 << ".";

}
