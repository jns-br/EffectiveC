#pragma once

#include <cstddef>

namespace my {
    template<typename T>
    class vector 
    {
        public:
            vector();
            vector(const size_t& n);
            ~vector();
        private:
            T* data_;

    };
    
    template<typename T>
    vector<T>::vector() {}

    template<typename T>
    vector<T>::vector(const size_t& n) : data_(new T[n]) {} 

    template<typename T>
    vector<T>::~vector()
    {
        delete[] data_;
    }

}