#include <E/E.h>
#include <D/D.h>

#include <iostream>

void e(int r) {
    std::cout << "Hello from e" << std::endl;
    d(r);
    std::cout << "Bye from e" << std::endl;
}
