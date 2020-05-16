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
    cout << "    Own Vec Testing   " << endl;
    cout << "======================" << endl;

    using vec3f = Vec<float,3>;
    
    {
        cout << "Testing length method " << endl;
        vec3f a({1, 2, 2});
        cout << "Length of vec3f: " << a.length() << endl;
        assert(a.length() == 3);
        cout << "passed" << endl;
        cout << endl;
    }

    {
        cout << "Testing operator << " << endl;
        vec3f a({4, 4, 4});
        cout << "Values of vec3f: " << a << endl;
        cout << endl;
    }

    {
        cout << "Testing container info method" << endl;
        vec3f a ({1, 2, 3});
        vec3f b ({4, 5, 6});
        vector<vec3f> v = {a, b};
        info(v);
        cout << endl;
    }

    {
        cout << "Add 10 vec3fs with random floats to vector" << endl;
        vector<vec3f> v(10);
    
        random_device rd;
        mt19937 e2(rd());
        uniform_real_distribution<> dist(0, 101);

        auto randomVec = [&e2, &dist]() 
        {
            return vec3f({(float) dist(e2), (float) dist(e2), (float) dist(e2)});
        };

        generate(v.begin(), v.end(), randomVec);

        info(v);
        cout << endl;

        cout << "Add One" << endl;

        vector<vec3f> vCopy(v);

        vec3f oneVec({1, 1, 1});
        auto addOne = [&oneVec](vec3f& v) {return v += oneVec;};
        transform(v.begin(), v.end(), v.begin(), addOne);

        cout << endl;
        cout << "Testing addition" << endl;
        int counter = 0;
        auto comp = [&counter, &vCopy, &oneVec](const vec3f& val) 
        {
            assert(vCopy[counter] + oneVec == val);
            counter++;
        };
        
        for_each(v.begin(), v.end(), comp);
        cout << "Addition test passed" << endl;
        cout << endl;

        cout << "Partition container by length <90" << endl;
        cout << "Container before partitioning" << endl;
        info(v);

        stable_partition(v.begin(), v.end(), [](const vec3f& v){ return v.length() < 90;});

        cout << "Container after partitioning" << endl;
        info(v);
        cout << endl;

        cout << "Sort by length" << endl;
        sort(v.begin(), v.end(), [](const vec3f& a, const vec3f& b){ return a.length() > b.length();});
        info(v);

        cout << "Median info" << endl;
        vec3f median = v[4];
        cout << "Values: " << median << ", Length: " << median.length() << endl;
        cout << endl;

        cout << "Copy <80 to new container" << endl;
        vector<vec3f> copy80;
        copy_if(v.begin(), v.end(), back_inserter(copy80), [](const vec3f& v){return v.length() < 80;});
        info(copy80);

        cout << "Testing copy container" << endl;
        for_each(copy80.begin(), copy80.end(), [](const vec3f& val) {assert(val.length() < 80);});
        cout << "Copy container test passed" << endl;
        cout << endl;

        cout << "remove all elemtes with length >90 && <120 from original" << endl;
        cout << endl;
        auto to_be_erased = remove_if(v.begin(), v.end(), [](const vec3f& val) {return val.length() > 90 && val.length() < 120;});
        v.erase(to_be_erased, v.end());
        v.shrink_to_fit();
        info(v);

        cout << "testing removal of elements" << endl;
        for_each(v.begin(), v.end(), [](const vec3f& val) {assert(val.length() < 90 || val.length() > 120);});
        cout << "removal test passed" << endl;

    }
    
    cout << "all Vec tests passed." << endl << endl;   

#endif // not NDEBUG

}