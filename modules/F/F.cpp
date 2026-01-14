#include "F.h"

#include <A/A.h>
#include <E/E.h>

#include <iostream>

void f(int r) {
    std::cout << "Hello from f" << std::endl;
    e(r);
    a(r);
    std::cout << "Bye from f" << std::endl;   
}
