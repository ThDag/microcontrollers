#include <iostream>

/*
 * intention; using the variable initialization commands.
 * making sure to use their unique properties
 */

int main()
{
    // this defines the variable but THEN gives it a value. therefore doesn't initiate it.
    int x;
    x = 5;

    // direct initialization. this does narrowing conversion giving the variable the value "5" because it is int. not float
    int y ( 5.4 );
    std::cout << y;

    // copy initialization. same as direct initialization.
    int z = 5.4;
    std::cout << z;

    // the alpha male of the inializations. the list initialization, aka uniform initialization. doesn't do narrowing conversion
    int q { 5 };

    [[maybe_unused]] int w { 4 };
}
