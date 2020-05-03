#pragma once

#include <array>

namespace my {
    template<typename T, int N>
    class Vec {
        public:
            template<typename ... Args>
            Vec(const T& first, const Args& ... rest) : v_({first, rest...})
            {
                static_assert(N == 1 + sizeof... (Args), "Vec: Wrong number of arguments");
            }

            T operator[] (int index) const;
            T& operator[] (int index);
            bool operator== (const Vec<T,N>& vec) const;
            bool operator!= (const Vec<T,N>& vec) const;
            Vec<T,N> operator+= (const Vec<T,N>& vec);
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


    //float dot(const Vec& vecA, const Vec& vecB);
}