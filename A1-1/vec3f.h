#pragma once

#include <array>

namespace my {
    class Vec3f {
        public:
            Vec3f(float x=0, float y=0, float z=0);

            float operator[] (const int& index) const;
            float& operator[] (const int& index);
            bool operator== (const Vec3f& vec3f) const;
            bool operator!= (const Vec3f& vec3f) const;
            Vec3f& operator+= (const Vec3f& vec3f);
            Vec3f operator+ (const Vec3f& vec3f) const;
            Vec3f operator- () const;
        
        private:
            std::array<float, 3> vec3f_;

    };

    float dot(const Vec3f& vec3fA, const Vec3f& vec3fB);
}