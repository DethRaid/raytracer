#include <iostream>
#include <fstream>
#include <cfloat>
#include <ctime>
#include <GL/glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ray.h"
#include "scene.h"
#include "surfaces/sphere.h"
#include "camera.h"
#include "materials/material.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "utils.h"
#include "materials/dialectric.h"
#include "bvh/bvh_node.h"
#include "materials/textures/constant_texture.h"
#include "materials/textures/image_texture.h"

glm::vec3 color(const ray &r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX, rec)) {
        ray scattered;
        glm::vec3 attenuation;
        if(depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return glm::vec3(0);
        }
    } else {
        glm::vec3 unit_direction = glm::normalize(r.direction());
        float t = 0.5f * (unit_direction.y + 1.0f);
        return glm::vec3(1.0) * (1.0f - t) + t * glm::vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 400;
    int ny = 200;
    int ns = 100;   // Number of rays per pixel
    srand((unsigned int) time(NULL));

    std::ofstream out("out.ppm");

    out << "P3\n" << nx << " " << ny << "\n255\n";

    std::vector<hitable *> surfaces;

    int width, height, nn;
    unsigned char * tex_data = stbi_load("img/earthmap.jpg", &width, &height, &nn, 0);

    surfaces.push_back(
            new sphere(
                    glm::vec3(0, 0, -1),
                    0.5,
                    new lambertian(new image_texture(tex_data, width, height))
            )
    );
    surfaces.push_back(
            new sphere(
                    glm::vec3(0, -100.5, -1),
                    100,
                    new lambertian(new image_texture(tex_data, width, height))
            )
    );
    surfaces.push_back(
            new sphere(
                    glm::vec3(1, 0, -1),
                    0.5,
                    new metal(new constant_texture(glm::vec3(0.8, 0.6, 0.2)), 0.3)));
    surfaces.push_back(
            new sphere(
                    glm::vec3(-1, 0, -1),
                    0.5,
                    new dialectric(0.5)));

    hitable *world = new bvh_node(surfaces, 0, 0);
    glm::vec3 lookfrom(1, 1, 2);
    glm::vec3 lookat(0, 0, -1);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 0.1;

    camera cam(lookfrom, lookat, glm::vec3(0, 1, 0), 30, float(nx) / float(ny), aperture, dist_to_focus);

    for(int j = ny - 1; j >= 0; j-- ) {
        for(int i = 0; i < nx; i++) {
            glm::vec3 col(0);

            for(int s = 0; s < ns; s++) {
                float u = (i + drand()) / float(nx);
                float v = (j + drand()) / float(ny);

                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = glm::vec3(sqrt(col.r), sqrt(col.g), sqrt(col.z));

            int ir = int(255.99 * col.r);
            int ig = int(255.99 * col.g);
            int ib = int(255.99 * col.b);

            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}