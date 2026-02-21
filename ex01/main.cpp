#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./RPN \"equation here\"" << std::endl;
        return 1;
    }

    RPN rpn;
    rpn.calculateFormula(argv[1]);
    return 0;
}
