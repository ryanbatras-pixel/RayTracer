#pragma once

#include <fstream>
#include <vector>

#include "sphere.h"
#include "camera.h"

class Renderer {

public:

    int width=800;
    int height=600;

    void render(
        std::vector<Sphere>& objects)
    {
        Camera camera;

        std::ofstream img("output.ppm");

        img<<"P3\n";
        img<<width<<" "<<height<<"\n255\n";

        Vec3 light(5,5,0);

        for(int y=0;y<height;y++)
        {
            for(int x=0;x<width;x++)
            {
                double u=
                  (2.0*x-width)/width;

                double v=
                  (height-2.0*y)/height;

                Ray ray=
                  camera.getRay(u,v);

                Vec3 pixel(135,206,235);

                double closest=1e9;

                for(auto& sphere:objects)
                {
                    double t;

                    if(sphere.intersect(ray,t))
                    {
                        if(t<closest)
                        {
                            closest=t;

                            Vec3 hit=
                              ray.origin+
                              ray.direction*t;

                            Vec3 normal=
                              (hit-sphere.center)
                              .normalize();

                            Vec3 lightDir=
                              (light-hit)
                              .normalize();

                            double intensity=
                              std::max(
                                0.0,
                                normal.dot(lightDir));

                            pixel=
                              sphere.color*
                              intensity;
                        }
                    }
                }

                int r=
                  std::min(255,
                  (int)(pixel.x*255));

                int g=
                  std::min(255,
                  (int)(pixel.y*255));

                int b=
                  std::min(255,
                  (int)(pixel.z*255));

                img<<r<<" "<<g<<" "<<b<<"\n";
            }
        }

        img.close();
    }
};
