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
            size_t size() const;
            void clear();
            void change_size(const size_t& new_size);
            void push_back(const T& val);
            T pop_back();
            T operator[](const size_t& index) const;
            T& operator[](const size_t& index);
            T at(const size_t& index) const;
            T& at(const size_t& index);

            vector(vector<T> const &) = delete;
            vector<T>& operator=(vector<T> const &) = delete;
        private:
            T* data_;
            size_t size_;
    };
    
    template<typename T>
    vector<T>::vector() : data_(nullptr), size_(0) {}

    template<typename T>
    vector<T>::vector(const size_t& n) : data_(new T[n]), size_(0)  {}

    template<typename T>
    vector<T>::vector(const size_t& n, const T& val) : data_(new T[n]), size_(n)
    {
        for (int i = 0; i < n; i++)
        {
           data_[i] = val;
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
        return size_ == 0;
    }

    template<typename T>
    void vector<T>::clear()
    {
        delete[] data_; 
        size_ = 0;
    }

    template<typename T>
    size_t vector<T>::size() const
    {
        return size_;
    }

    template<typename T>
    void vector<T>::change_size(const size_t& new_size)
    {
        
        T* tmp = new T[new_size];
        if (new_size >= size_)
        {
            for(int i = 0; i < size_; ++i)
            {
                tmp[i] = data_[i];
            }
        }
        else
        {
            for(int i = 0; i < new_size; ++i)
            {
                tmp[i] = data_[i];
            }
        }
        

        size_ = new_size;
        delete[] data_;
        data_ = tmp;
        
    } 

    template<typename T>
    void vector<T>::push_back(const T& val)
    {
        
        change_size(size_ + 1);

        data_[size_ - 1] = val;
    }

    template<typename T>
    T vector<T>::pop_back()
    {
        T val = data_[size_ - 1];
        change_size(size_ - 1);
        return val;
    }

    template<typename T>
    T vector<T>::operator[](const size_t& index) const
    {
        return data_[index];
    }

    template<typename T>
    T& vector<T>::operator[](const size_t& index)
    {
        return data_[index];
    }

    template<typename T>
    T vector<T>::at(const size_t& index) const
    {
        if (index > size_ - 1)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return data_[index];
        }
    }

    template<typename T>
    T& vector<T>::at(const size_t& index)
    {
        if (index > size_ - 1)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return data_[index];
        }
        
    }

}