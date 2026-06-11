#include "camera.h"
#include "scene.h"

int main() {
    auto world = impressive_scene();

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 700;
    cam.samples_per_pixel = 80;
    cam.max_depth = 20;
    cam.background = color(0.012, 0.014, 0.020);

    cam.vfov = 36;
    cam.lookfrom = point3(5.2, 2.7, 5.6);
    cam.lookat = point3(0.1, 0.7, -0.15);
    cam.vup = vec3(0, 1, 0);
    cam.defocus_angle = 0.35;
    cam.focus_dist = 6.8;

    cam.render(world, "render.ppm");
    return 0;
}
