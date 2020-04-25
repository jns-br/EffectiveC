#pragma once

#include <array>

namespace my {
    class Vec3f {
        public:
            Vec3f(float x, float y, float z);

            std::array<float, 3> vec3f() const;
            void set_vec3f(std::array<float, 3> vec3f);
        
        private:
            std::array<float, 3> vec3f_;

    };
}