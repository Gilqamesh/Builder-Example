#include <modules/B/B.h>
#include <modules/A/A.h>

#include <iostream>

void b(int r) {
    if (!r) {
        return ;
    }
    std::cout << "Hello from b" << std::endl;
    a(r - 1);
    std::cout << "Bye from b" << std::endl;
}
