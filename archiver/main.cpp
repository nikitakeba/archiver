#include <iostream>

#include "parser.h"

int main(int argc, char *argv[]) {
    try {
        Parse(argc, argv);
    } catch (...) {
        std::cout << "Error";
    }
}
