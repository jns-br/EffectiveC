#include "vec3f.h"

using namespace my;

Vec3f::Vec3f(float x, float y, float z)
    : vec3f_({x, y, z})
{}

std::array<float, 3>
Vec3f::vec3f() const
{
    return vec3f_;
}

void
Vec3f::set_vec3f(std::array<float, 3> vec3f)
{
    vec3f_ = vec3f;
}

float
Vec3f::operator[] (int index) const
{
    return vec3f_[index];
}