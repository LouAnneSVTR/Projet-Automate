#include <iostream>
#include "set.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    univ_nantes::set<int> s = {1, 2, 3, 4};

    univ_nantes::set<int> sBis;

    sBis = s;



    return 0;
}
