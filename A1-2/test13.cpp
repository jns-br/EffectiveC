#include <iostream>
#include <cassert>
#include <typeinfo>
#include <vector>
#include <random>
#include <algorithm>

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
        cout << "info test ";
        vec3f a ({1, 2, 3});
        vec3f b ({4, 5, 6});
        vector<vec3f> v = {a, b};
        info(v);
        cout << "passed" 
        << endl;
    }

    {
        cout << "Add 10 vec3fs to vector" << endl;
        std::vector<vec3f> v(10);
    
        
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<> dist(0, 101);

        auto randomVec = [&e2, &dist]() 
        {
            return vec3f({(float) dist(e2), (float) dist(e2), (float) dist(e2)});
        };

        std::generate(v.begin(), v.end(), randomVec);

        std::for_each(v.begin(), v.end(), [](const vec3f& v){cout << v << endl;});

        cout << "Add One" << endl;

        vec3f oneVec({1, 1, 1});
        auto addOne = [&oneVec](vec3f& v) {return v += oneVec;};
        std::transform(v.begin(), v.end(), v.begin(), addOne);
        
        std::for_each(v.begin(), v.end(), [](const vec3f& v){cout << v << endl;});

        cout << "Partition" << endl;
        cout << "Length before" << endl;
        std::for_each(v.begin(), v.end(), [](const vec3f& v){cout << v.length() << endl;});

        std::stable_partition(v.begin(), v.end(), [](vec3f v){ return v.length() > 90;});

        cout << "Length after" << endl;
        std::for_each(v.begin(), v.end(), [](const vec3f& v){cout << v.length() << endl;});

    }
    
    cout << "all Vec tests passed." << endl << endl;   

#endif // not NDEBUG

}