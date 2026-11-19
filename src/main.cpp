#include <exception>
#include <iostream>

#include "menu.h"

int main() {
    try {
        lab4::run_menu(std::cin, std::cout);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
