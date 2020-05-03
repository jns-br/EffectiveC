#include <iostream>
#include "vec3.h"
#include "test11.h"
#include <array>

int main()
{
    my::Vec<float,4> x({1.0f, 2.3f, 3.4f, 4.5f});
    my::Vec<float,4> y({1.0f, 1.0f, 1.0f, 1.0f});
    
    std::array<float,4> arr = {1.0f, 2.0f, 3.0f, 4.0f};
    
    my::Vec<float,4> tmp = x + y;

    my::Vec<float,4> z({-2.0f, -3.3f, -4.4f, -5.5f});

    

    std::cout << (-tmp == z) << std::endl;
    return 0;
}