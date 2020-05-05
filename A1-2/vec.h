#pragma once

#include <array>

namespace my {
    template<typename T, size_t N>
    class Vec {
        public:
            Vec();
            Vec(std::array<T,N> const& v);

            T operator[] (int index) const;
            T& operator[] (int index);
            bool operator== (const Vec<T,N>& vec) const;
            bool operator!= (const Vec<T,N>& vec) const;
            Vec<T,N>& operator+= (const Vec<T,N>& vec);
            Vec<T,N> operator+ (const Vec<T,N>& vec) const;
            Vec<T,N> operator- () const;
        
        private:
            std::array<T, N> v_;

    };

    template<typename T, size_t N>
    Vec<T,N>::Vec() {}

    template<typename T, size_t N>
    Vec<T,N>::Vec(std::array<T,N> const& v) : v_(v) {}

    template<typename T, size_t N>
    T Vec<T,N>::operator[] (int index) const 
    {
        return v_[index];
    };

    template<typename T, size_t N>
    T& Vec<T,N>::operator[] (int index) 
    {
        return v_[index];
    };

    template<typename T, size_t N>
    bool Vec<T,N>::operator== (const Vec<T,N>& vec) const 
    {
        for (size_t i = 0; i < N; i++)
        {
            if (v_[i] != vec[i])
            {
                return false;
            }
        }

        return true; 
    };

    template<typename T, size_t N>
    bool Vec<T,N>::operator!= (const Vec<T,N>& vec) const 
    {
        return !(*this == vec);
    }

    template<typename T, size_t N>
    Vec<T,N>& Vec<T,N>::operator+= (const Vec<T,N>& vec) 
    {
        for (size_t i = 0; i < N; i++)
        {
            v_[i] += vec[i];
        }

        return *this;   
    }

    template<typename T, size_t N>
    Vec<T,N> Vec<T,N>::operator+ (const Vec<T,N>& vec) const 
    {
        Vec temp(*this);
        temp += vec;
        return temp;
    }

    template<typename T, size_t N>
    Vec<T,N> Vec<T,N>::operator- () const 
    {
        std::array<T,N> neg;
        for (size_t i = 0; i < N; i++)
        {
            neg[i] = -v_[i];
        }
        
        return Vec(neg);
    }

    template<typename T, size_t N>
    T dot(const Vec<T,N>& vecA, const Vec<T,N>& vecB)
    {
        T f = 0;

        for (size_t i = 0; i < N; i++)
        {
            f += vecA[i] * vecB[i];
        }
        
        return f;
    };
}