#pragma once

#include <cstddef>

namespace my {
    template<typename T>
    class vector 
    {
        public:
            vector();
            vector(const size_t& n);
            vector(const size_t& n, const T& val);
            ~vector();
            bool empty() const;
            void clear();
        private:
            T* data_;
            size_t size_;
            size_t capacity_;

    };
    
    template<typename T>
    vector<T>::vector() : data_(new T[0]), size_(0), capacity_(0) {}

    template<typename T>
    vector<T>::vector(const size_t& n) : data_(new T[n]), size_(0), capacity_(n)  {}

    template<typename T>
    vector<T>::vector(const size_t& n, const T& val) : data_(new T[n]), size_(n), capacity_(n)
    {
        for (int i = 0; i < n; i++)
        {
            this->data_[i] = val;
        }
        
    } 

    template<typename T>
    vector<T>::~vector()
    {
        delete[] data_;
    }

    template<typename T>
    bool vector<T>::empty() const
    {
        return this->size_ == 0;
    }

    template<typename T>
    void vector<T>::clear() 
    {
        this->size_ = 0;
    }

}