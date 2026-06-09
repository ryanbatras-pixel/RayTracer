#pragma once
#include "vec3.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray(Vec3 o, Vec3 d)
        : origin(o), direction(d) {}
};
