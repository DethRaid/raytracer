//
// Created by ddubois on 21-Aug-16.
//

#include <iostream>
#include <numeric>
#include <random>
#include <gl/glm/glm.hpp>
#include "ray.h"
#include "hitables/hitable.h"
#include "hitables/sphere.h"
#include "hitables/hitable_list.h"
#include "camera.h"

float get_random_float() {
    static std::random_device rd;

    return float(rd()) / float(rd.max());
}

glm::vec3 random_in_unit_sphere() {
    glm::vec3 p;
    do {
        p = glm::vec3(get_random_float(), get_random_float(), get_random_float()) * 2.0f - 1.0f;
        // CLion, Y U NO PARSE TEMPLATES RIGHT?
    } while(glm::length(p) >= 1.0f);
    return p;
}

glm::vec3 color(const ray& r, hitable* world) {
    hit_record rec;
    if(world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec)) {
        glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return color(ray(rec.p, target - rec.p), world) * 0.5f;
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin(0.0f);

    std::vector<hitable*> list;
    list.push_back(new sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
    list.push_back(new sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

    hitable *world = new hitable_list(list);

    camera cam;

    for(int j = ny - 1; j >= 0; j--) {
        for(int i = 0; i < nx; i++) {
            glm::vec3 col(0);
            for(int s = 0; s < ns; s++) {
                float u = float(i + get_random_float()) / float(nx);
                float v = float(j + get_random_float()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);

            int ir = int(255.99 * col.r);
            int ig = int(255.99 * col.g);
            int ib = int(255.99 * col.b);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}