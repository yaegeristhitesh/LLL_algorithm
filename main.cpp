/*
Written by Ashutosh Vishwakarma
And Hitesh Choudhary
Date 16-04-2023
*/


#include <iostream>
#include "Vector_class.h"


int main() {
    bool a = true;
    while (a) {
        int n, m;
        std::cout << "Enter row x width separated by space" << std::endl;
        std::cin >> n >> m;
        Basis b(n, m);
        std::cout << "Enter the " << n << "x" << m << " basis" << std::endl;
        b.inputBasis();
        b.LLL();
        std::cout << "Output " << std::endl;
        b.printBasis();

        std::cout << "Do you want to continue? (y/n)" << std::endl;
        char in;
        std::cin >> in;
        if (in == 'n' || in == 'N') a = false;
    }
    


    return 0;
}