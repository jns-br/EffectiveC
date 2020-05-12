#pragma once

#include <array>
#include <algorithm>
#include <numeric>

namespace my {
    template<typename T, size_t N>
    class Vec {
        public:
            Vec();
            Vec(const std::array<T,N>& v);

            T operator[] (const int& index) const;
            T& operator[] (const int& index);
            bool operator== (const Vec<T,N>& vec) const;
            bool operator!= (const Vec<T,N>& vec) const;
            Vec<T,N>& operator+= (const Vec<T,N>& vec);
            Vec<T,N> operator+ (const Vec<T,N>& vec) const;
            Vec<T,N> operator- () const;
            friend T dot(const Vec<T,N>& vecA, const Vec<T,N>& vecB);
        
        private:
            std::array<T, N> v_;

    };

    template<typename T, size_t N>
    Vec<T,N>::Vec() {}

    template<typename T, size_t N>
    Vec<T,N>::Vec(const std::array<T,N>& v) : v_(v) {}

    template<typename T, size_t N>
    T Vec<T,N>::operator[] (const int& index) const 
    {
        return v_[index];
    };

    template<typename T, size_t N>
    T& Vec<T,N>::operator[] (const int& index) 
    {
        return v_[index];
    };

    template<typename T, size_t N>
    bool Vec<T,N>::operator== (const Vec<T,N>& vec) const 
    {
        return std::equal(v_.begin(), v_.end(), vec.v_.begin()); 
    };

    template<typename T, size_t N>
    bool Vec<T,N>::operator!= (const Vec<T,N>& vec) const 
    {
        return !(*this == vec);
    }

    template<typename T, size_t N>
    Vec<T,N>& Vec<T,N>::operator+= (const Vec<T,N>& vec) 
    {   
        auto add = [](T val1, T val2){return val1 + val2;};
        std::transform(v_.begin(), v_.end(), vec.v_.begin(), v_.begin(), add);

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
        std::array<T,N> neg(v_);
        auto negate = [](T val1) {return -val1;};
        std::transform(neg.begin(), neg.end(), neg.begin(), negate);
        

        return Vec(neg);
    }

    template<typename T, size_t N>
    T dot( Vec<T,N> const& vecA, Vec<T,N> const& vecB)
    {
        T f = std::inner_product(vecA.v_.begin(), vecA.v_.end(), vecB.v_.begin(), 0);
        return f;
    };
}