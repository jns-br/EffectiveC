#include <iostream>
#include <cassert>
#include <typeinfo>
#include <vector>
using namespace std;

#include "vec.h"
using namespace my;

void test_vec_13() {

#ifndef NDEBUG
    cout << "======================" << endl;
    cout << "     Testing Vec      " << endl;
    cout << "======================" << endl;

    using vec3f = Vec<float,3>;

    {
        // do not tolerate any memory overhead
        cout << "  sizeof(Vec3f) == 3 bytes: ";
        assert( sizeof(vec3f) == 3*sizeof(float) );
        cout << "passed." << endl;
    }
    
    {
        cout << " length method ";
        vec3f a({4, 4, 4});
        cout << a.length() << endl;
    }

    {
        cout << "operator << ";
        vec3f a({4, 4, 4});
        cout << a << endl;
    }

    {
        cout << "info test " << endl;
        vec3f a ({1, 2, 3});
        vec3f b ({4, 5, 6});
        vector<vec3f> v = {a, b};
        info(v);
    }
    
    cout << "all Vec tests passed." << endl << endl;   

#endif // not NDEBUG

}