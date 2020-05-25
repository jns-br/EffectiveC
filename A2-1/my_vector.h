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
            void change_capacity(size_t new_cap);
            void push_back(const T& val);
            T pop_back();
            T operator[](size_t index) const;
            T& operator[](size_t index);
            T at(size_t index) const;
            T& at(size_t index);

            vector(vector<T> const &) = delete;
            vector<T>& operator=(vector<T> const &) = delete;
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

    template<typename T>
    size_t vector<T>::size() const
    {
        return this->size_;
    }

    template<typename T>
    void vector<T>::change_capacity(size_t new_cap)
    {
        if(new_cap == this->capacity_) 
        {
            return;
        }

        T* tmp = new T[new_cap];
        if(new_cap > this->size_)
        {
            for(int i = 0; i < this->size_; ++i)
            {
                tmp[i] = this->data_[i];
            }
        } 
        else
        {
            for(int i = 0; i < new_cap; ++i) 
            {
                tmp[i] = this->data_[i];
            }
        }

        this->capacity_ = new_cap;
        delete[] this->data_;
        this->data_ = tmp;
        
    } 

    template<typename T>
    void vector<T>::push_back(const T& val)
    {
        if (this->size_ == this->capacity)
        {
            change_capacity(this->capacity_ + 1);
        }

        this->data_[this->size_++] = val;
    }

    template<typename T>
    T vector<T>::pop_back()
    {
        return this->data_[--this->size_];
    }

    template<typename T>
    T vector<T>::operator[](size_t index) const
    {
        return this->data_[index];
    }

    template<typename T>
    T& vector<T>::operator[](size_t index)
    {
        return this->data_[index];
    }

    template<typename T>
    T vector<T>::at(size_t index) const
    {
        if (index > this->size_ - 1)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return this->data_[i];
        }
    }

    template<typename T>
    T& vector<T>::at(size_t index)
    {
        if (index > this->size - 1)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return this->data_[i];
        }
        
    }

}