#include <vector>

#include "renderer.h"

int main()
{
    std::vector<Sphere> scene;

    scene.push_back(
        Sphere(
            Vec3(0,0,-5),
            1,
            Vec3(1,0,0)));

    scene.push_back(
        Sphere(
            Vec3(2,0,-6),
            1,
            Vec3(0,1,0)));

    scene.push_back(
        Sphere(
            Vec3(-2,0,-6),
            1,
            Vec3(0,0,1)));

    Renderer renderer;

    renderer.render(scene);

    return 0;
}
