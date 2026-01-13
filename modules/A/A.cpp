#include <A/A.h>
#include <C/C.h>

#include <iostream>

void a(int r) {
    if (!r) {
        return ;
    }
    std::cout << "Hello from a" << std::endl;
    c(r - 1);
    std::cout << "Bye from a" << std::endl;
}
