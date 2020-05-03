#include <iostream>
#include "vec3.h"
#include "test11.h"

int main()
{
    my::Vec<float,4> x(1.0f, 2.3f, 3.4f, 4.5f);
    my::Vec<float,4> y(1.0f, 2.3f, 3.4f, 4.5f);


    float f = x[1];
    std::cout << f << std::endl;

    bool comp = x == y;
    std::cout << comp << std::endl;

    bool comp2 = x != y;
    std::cout << comp2 << std::endl;
    return 0;
}