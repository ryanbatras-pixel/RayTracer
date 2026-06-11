#include "camera.h"
#include "scene.h"

int main() {

    auto world = solar_system_scene();

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;

    cam.image_width = 1200;

    cam.samples_per_pixel = 100;

    cam.max_depth = 20;

    cam.background = color(0.01, 0.01, 0.03);

    cam.vfov = 25;

    cam.lookfrom = point3(26, 8, 18);

    cam.lookat = point3(8, 1, 0);

    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.1;

    cam.focus_dist = 25.0;

    cam.render(world, "solar_system.ppm");

    return 0;
}
