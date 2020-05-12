#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;

#include "vec.h"
using namespace my;

void test_vec_13() {

#ifndef NDEBUG
    cout << "======================" << endl;
    cout << "     Testing Vec      " << endl;
    cout << "======================" << endl;

    using Vec3f = Vec<float,3>;

    {
        // do not tolerate any memory overhead
        cout << "  sizeof(Vec3f) == 3 bytes: ";
        assert( sizeof(Vec3f) == 3*sizeof(float) );
        cout << "passed." << endl;
    }
    
    {
        cout << " length method ";
        Vec3f a({4, 4, 4});
        cout << a.length() << endl;
    }
    
    cout << "all Vec tests passed." << endl << endl;   

#endif // not NDEBUG

}