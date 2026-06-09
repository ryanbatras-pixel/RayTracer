#pragma once
#include <cmath>

class Vec3 {
public:
    double x,y,z;

    Vec3() : x(0), y(0), z(0) {}

    Vec3(double x,double y,double z)
        : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x+v.x,y+v.y,z+v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x-v.x,y-v.y,z-v.z);
    }

    Vec3 operator*(double s) const {
        return Vec3(x*s,y*s,z*s);
    }

    double dot(const Vec3& v) const {
        return x*v.x+y*v.y+z*v.z;
    }

    Vec3 normalize() const {
        double len=sqrt(dot(*this));
        return (*this)*(1.0/len);
    }
};
