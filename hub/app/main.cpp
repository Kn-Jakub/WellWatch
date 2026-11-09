#include <iostream>

#include "wellwatch/core/version.hpp"

int main() {
    std::cout << "wellwatch-hub " << wellwatch::core::version() << '\n';
    return 0;
}
