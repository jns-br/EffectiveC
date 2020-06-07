#pragma once

#include <cstddef>
#include <utility>

namespace my {
    template<typename T>
    class vector 
    {
        public:
            vector();
            vector(const size_t& n);
            vector(const size_t& n, const T& val);
            vector(const vector<T>& vector);
            vector(vector<T>&& vector);
            ~vector();
            bool empty() const;
            size_t size() const;
            size_t capacity() const;
            void clear();
            void reserve(const size_t& new_capacity);
            void shrink_to_fit();
            void change_size(const size_t& new_size);
            void push_back(const T& val);
            T pop_back();
            T operator[](const size_t& index) const;
            T& operator[](const size_t& index);
            T& operator=(vector<T> vector);
            T at(const size_t& index) const;
            T& at(const size_t& index);

            template<typename X> friend void swap(vector<X>& a, vector<X>& b);
        private:
            T* data_;
            size_t size_;
            size_t capacity_;
            void* memory_;
    };
    
    template<typename T>
    vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

    template<typename T>
    vector<T>::vector(const size_t& n) : size_(0), capacity_(n)  
    {
        memory_ = malloc(sizeof(T) * n);
        data_ = new(memory_) T[n];
    }

    template<typename T>
    vector<T>::vector(const size_t& n, const T& val) : size_(n), capacity_(n)
    {
        memory_ = malloc(sizeof(T) * n);
        data_ = new(memory_) T[n];
        for (int i = 0; i < n; i++)
        {
            this->data_[i] = val;
        }
        
    }

    template<typename T>
    vector<T>::vector(const vector<T>& vector) : data_(*vector.data_), size_(vector.size_), capacity_(vector.capacity_), memory_(*vector.memory_) {}

    template<typename T>
    vector<T>::vector(vector<T>&& vector) : vector<T>()
    {
        swap(*this, vector);
    } 

    template<typename T>
    vector<T>::~vector()
    {
        delete[] data_;
        free(memory_);
    }

    template<typename T>
    bool vector<T>::empty() const
    {
        return this->size_ == 0;
    }

    template<typename T>
    size_t vector<T>::size() const
    {
        return this->size_;
    }

    template<typename T>
    size_t vector<T>::capacity() const
    {
        return this->capacity_;
    }

    template<typename T>
    void vector<T>::reserve(const size_t& new_capacity)
    {
        auto tmp = this->data_;
        delete[] this->data_;
        free(memory_);
        memory_ = malloc(sizeof(T) * new_capacity);
        this->data_ = new(memory_) T[new_capacity];

        if (new_capacity >= this->size_)
        {
            for (int i = 0; i < this->size_; i++)
            {
                this->data_[i] = tmp[i];
            }
        } 
        else
        {
            for (int i = 0; i < new_capacity; i++)
            {
                this->data_[i] = tmp[i];
            }
            this->size_ = new_capacity;
        }

        this->capacity_ = new_capacity;
    }

    template<typename T>
    void vector<T>::shrink_to_fit()
    {
        if(this->capacity_ > this->size_)
        {
            reserve(this->size_);
        }
    }

    template<typename T>
    void vector<T>::clear()
    {
        delete[] this->data_; 
        this->size_ = 0;
    }

    template<typename T>
    void vector<T>::change_size(const size_t& new_size)
    {
        
        T* tmp = new T[new_size];
        if (new_size >= this->size_)
        {
            for(int i = 0; i < this->size_; ++i)
            {
                tmp[i] = this->data_[i];
            }
        }
        else
        {
            for(int i = 0; i < new_size; ++i)
            {
                tmp[i] = this->data_[i];
            }
        }
        

        this->size_ = new_size;
        delete[] this->data_;
        this->data_ = tmp;
        
    } 

    template<typename T>
    void vector<T>::push_back(const T& val)
    {
        this->size_++;
        if (this->size_ > this->capacity_)
        {
            reserve(this->size_);
        }

        this->data_[this->size_ - 1] = val;
    }

    template<typename T>
    T vector<T>::pop_back()
    {
        this->size_--;
        T val = this->data_[this->size_];
        delete data_[this->size_];
        return val;
    }

    template<typename T>
    T vector<T>::operator[](const size_t& index) const
    {
        return this->data_[index];
    }

    template<typename T>
    T& vector<T>::operator[](const size_t& index)
    {
        return this->data_[index];
    }

    template<typename T>
    T& vector<T>::operator=(vector<T> vector)
    {
        swap(*this, vector);
        return *this;
    }

    template<typename T>
    T vector<T>::at(const size_t& index) const
    {
        if (index > this->size_ - 1)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return this->data_[index];
        }
    }

    template<typename T>
    T& vector<T>::at(const size_t& index)
    {
        if (index > this->size_ - 1)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return this->data_[index];
        }
        
    }

    template<typename X>
    void swap(vector<X>& a, vector<X>& b)
    {
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
        swap(a.capacity_, b.capacity_);
        swap(a.memory_, b.memory_);
    }

}