#pragma once

#include <array>

namespace my {
    template<typename T, int N>
    class Vec {
        public:
            Vec(std::array<T,N> const& v) : v_(v)
            {}

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

    template<typename T, int N>
    T Vec<T,N>::operator[] (int index) const {
        //static_assert(index >= 0 && index < N, "Vec[]: Index out of bounds");

        return v_[index];
    };

    template<typename T, int N>
    T& Vec<T,N>::operator[] (int index) {
        //static_assert(index >= 0 && index < N, "Vec[]: Index out of bounds");

        return v_[index];
    };

    template<typename T, int N>
    bool Vec<T,N>::operator== (const Vec<T,N>& vec) const {
        for (int i = 0; i < N; i++)
        {
            if (v_[i] != vec[i])
            {
                return false;
            }
        }

        return true; 
    };

    template<typename T, int N>
    bool Vec<T,N>::operator!= (const Vec<T,N>& vec) const {
        return !(*this == vec);
    }

    template<typename T, int N>
    Vec<T,N>& Vec<T,N>::operator+= (const Vec<T,N>& vec) {
        for (int i = 0; i < N; i++)
        {
            v_[i] += vec[i];
        }

        return *this;   
    }

    template<typename T, int N>
    Vec<T,N> Vec<T,N>::operator+ (const Vec<T,N>& vec) const {
        Vec temp(*this);
        temp += vec;
        return temp;
    }

    template<typename T, int N>
    Vec<T,N> Vec<T,N>::operator- () const {
        
        return Vec(v_);
    }

    //float dot(const Vec& vecA, const Vec& vecB);
}