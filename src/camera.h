#pragma once

#include "ray.h"

class Camera {
public:
    Vec3 position;

    Camera()
        : position(0,0,0) {}

    Ray getRay(double u,double v) {

        Vec3 viewport(u,v,-1);

        return Ray(position,
                   viewport.normalize());
    }
};
