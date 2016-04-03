#include <iostream>
#include <fstream>
#include <cfloat>
#include <ctime>
#include <cstdlib>

#include "vec3.h"
#include "ray.h"
#include "scene.h"
#include "surfaces/sphere.h"
#include "camera.h"
#include "materials/material.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "utils.h"
#include "materials/dialectric.h"

vec3 color(const ray &r, surface *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;   // Number of rays per pixel
    srand((unsigned int) time(NULL));

    std::ofstream out("out.ppm");

    out << "P3\n" << nx << " " << ny << "\n255\n";

    std::vector<surface *> surfaces;

    surfaces.push_back(new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5))));
    surfaces.push_back(new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0))));
    surfaces.push_back(new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3)));
    surfaces.push_back(new sphere(vec3(-1, 0, -1), -0.5, new dialectric(0.5)));

    surface *world = new scene(surfaces);
    vec3 lookfrom(3, 3, 2);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 2.0;

    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

    for(int j = ny - 1; j >= 0; j-- ) {
        for(int i = 0; i < nx; i++) {
            vec3 col(0);

            for(int s = 0; s < ns; s++) {
                float u = (i + drand()) / float(nx);
                float v = (j + drand()) / float(ny);

                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.z()));

            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());

            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}