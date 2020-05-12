#pragma once

#include <array>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

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
            T length() const;
            template<typename TD, size_t ND> friend TD dot(const Vec<TD,ND>& vecA, const Vec<TD,ND>& vecB);
        
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
    T Vec<T,N>::length() const
    {   
        /*
        C++ 17 function
        T l = std::transform_reduce(v_.begin(), v_.end(), 0.0, std::plus<T>(), [](T  val) {return std::pow(val, 2);});
        return std::sqrt(l);
        */
        std::array<T,N> exp(v_) ;
        std::transform(exp.begin(), exp.end(), exp.begin(), [](T  val) {return std::pow(val, 2);});
        T l = std::accumulate(exp.begin(), exp.end(), 0);
        return std::sqrt(l);
        
    }

    template<typename TD, size_t ND>
    TD dot(const Vec<TD,ND>& vecA, const Vec<TD,ND>& vecB)
    {
        TD f = std::inner_product(vecA.v_.begin(), vecA.v_.end(), vecB.v_.begin(), 0);
        return f;
    };
}