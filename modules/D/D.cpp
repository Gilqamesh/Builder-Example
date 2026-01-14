#include "D.h"

#include <E/E.h>

#include <iostream>

void d(int r) {
    if (!r) {
        return ;
    }

    const std::string prefix(r * 2, ' ');
    std::cout << prefix << "Hello from d" << std::endl;
    e(r - 1);
    std::cout << prefix << "Bye from d" << std::endl;
}
