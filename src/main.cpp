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

float drand() {
    return rand() / static_cast<float>(RAND_MAX);
}

vec3 random_inside_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand(), drand(), drand()) - vec3(1);
    } while(p.squared_length() >= 1.0);

    return p;
}

vec3 color(const ray &r, surface *world) {
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX, rec)) {
        vec3 target = rec.p + rec.normal + random_inside_unit_sphere();
        return 0.5 * color(ray(rec.p, target - rec.p), world);
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

    vec3 lower_left_corner(-2, -1, -1);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0);

    std::vector<surface *> surfaces(2);
    surfaces[0] = new sphere(vec3(0, 0, -1), 0.5);
    surfaces[1] = new sphere(vec3(0, -100.5, -1), 100);
    surface *world = new scene(surfaces);
    camera cam;

    for(int j = ny - 1; j >= 0; j-- ) {
        for(int i = 0; i < nx; i++) {
            vec3 col(0);

            for(int s = 0; s < ns; s++) {
                float u = float(i + drand()) / float(nx);
                float v = float(j + drand()) / float(ny);

                ray r = cam.get_ray(u, v);
                col += color(r, world);
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