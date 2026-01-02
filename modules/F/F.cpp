#include <modules/F/F.h>
#include <modules/A/A.h>
#include <modules/E/E.h>

#include <iostream>

void f(int r) {
    std::cout << "Hello from f" << std::endl;
    e(r);
    a(r);
    std::cout << "Bye from f" << std::endl;
    
}