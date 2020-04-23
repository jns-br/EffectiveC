
#include <iostream>
#include "A.h"
#include "dummy.h"

int main() 
{
    A a;
    std::cout << "Output of object a: " << a.info() << std::endl;
    std::cout << "my_dummy func returns " << my_dummy() << std::endl;
    return 0;
}