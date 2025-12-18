#include <modules/C/C.h>
#include <modules/B/B.h>

#include <iostream>

void c(int r) {
    std::cout << "Hello from c" << std::endl;
    b(r - 1);
    std::cout << "Bye from c" << std::endl;
}
