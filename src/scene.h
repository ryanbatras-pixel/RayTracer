#ifndef SCENE_H
#define SCENE_H

#include "material.h"
#include "sphere.h"

inline hittable_list impressive_scene() {
    hittable_list world;

    auto ground = make_shared<lambertian>(color(0.45, 0.42, 0.34));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground));

    auto glass = make_shared<dielectric>(1.5);
    auto copper = make_shared<metal>(color(0.95, 0.58, 0.32), 0.18);
    auto chrome = make_shared<metal>(color(0.82, 0.86, 0.90), 0.03);
    auto blue = make_shared<lambertian>(color(0.12, 0.24, 0.60));
    auto red = make_shared<lambertian>(color(0.75, 0.18, 0.12));
    auto light = make_shared<diffuse_light>(color(5.5, 4.5, 3.2));
    auto cyan_light = make_shared<diffuse_light>(color(1.0, 4.0, 5.5));

    world.add(make_shared<sphere>(point3(-1.15, 1.0, -1.0), 1.0, glass));
    world.add(make_shared<sphere>(point3(1.35, 0.9, -0.65), 0.9, copper));
    world.add(make_shared<sphere>(point3(0.05, 0.55, 1.05), 0.55, red));
    world.add(make_shared<sphere>(point3(-2.15, 0.42, 1.15), 0.42, chrome));
    world.add(make_shared<sphere>(point3(2.45, 0.35, 0.75), 0.35, blue));
    world.add(make_shared<sphere>(point3(-2.6, 2.1, -2.6), 0.45, light));
    world.add(make_shared<sphere>(point3(2.7, 1.35, 1.1), 0.30, cyan_light));

    for (int a = -6; a <= 6; a++) {
        for (int b = -4; b <= 4; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.55 * random_double(), 0.16, b + 0.55 * random_double());
            if ((center - point3(0, 0.16, 0)).length() < 1.25) continue;

            shared_ptr<material> sphere_material;
            if (choose_mat < 0.58) {
                auto albedo = color::random(0.18, 0.85) * color::random(0.18, 0.85);
                sphere_material = make_shared<lambertian>(albedo);
            } else if (choose_mat < 0.86) {
                auto albedo = color::random(0.55, 1.0);
                auto fuzz = random_double(0.0, 0.35);
                sphere_material = make_shared<metal>(albedo, fuzz);
            } else {
                sphere_material = make_shared<dielectric>(1.5);
            }

            world.add(make_shared<sphere>(center, 0.16, sphere_material));
        }
    }

    return world;
}

#endif
