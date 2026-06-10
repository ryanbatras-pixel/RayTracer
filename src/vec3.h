#pragma once
#include <cmath>

struct Vec3 {
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(double s) const {
        return Vec3(x * s, y * s, z * s);
    }

    double dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    double length() const {
        return std::sqrt(dot(*this));
    }

    Vec3 normalize() const {
        double len = length();
        return Vec3(x / len, y / len, z / len);
    }
};
