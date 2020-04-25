#pragma once

#include <array>

namespace my {
    class Vec3f {
        public:
            Vec3f(float x=0, float y=0, float z=0);

            float operator[] (int index) const;
            float& operator[] (int index);
            bool operator== (Vec3f vec3f) const;
            bool operator!= (Vec3f vec3f) const;
            Vec3f& operator+= (Vec3f vec3f);
            Vec3f operator+ (Vec3f vec3f) const;
            Vec3f operator- () const;
        
        private:
            std::array<float, 3> vec3f_;

    };

    inline float dot(Vec3f vec3fA, Vec3f vec3fB){
        return vec3fA[0] * vec3fB[0] + vec3fA[1] * vec3fB[1] + vec3fA[2] * vec3fB[2];
    };
}