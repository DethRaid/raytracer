//
// Created by ddubois on 21-Aug-16.
//

#include <iostream>
#include <numeric>
#include <random>
#include <math.h>
#include <thread>
#include <ctime>
#include "ray.h"
#include "hitables/hitable.h"
#include "hitables/sphere.h"
#include "hitables/hitable_list.h"
#include "materials/material.h"
#include "camera.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dialectric.h"
#include "output/output_window.h"

glm::vec3 color(const ray& r, hitable* world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.0001f, std::numeric_limits<float>::max(), rec)) {
        ray scattered;
        glm::vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            // If the ray reaches the max recursion depth (or is absorbed by a material) then that ray gets no light
            return glm::vec3(0);
        }
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

void render_screen_part(glm::ivec2 offset, glm::ivec2 size, camera& cam, hitable *world, std::vector<glm::vec3> &output_buffer) {
    for(int y = offset.y; y < size.y; y++) {
        for(int x = offset.x; x < size.x; x++) {
            glm::vec3 col(0);
            for(int s = 0; s < cam.samples; s++) {
                float u = float(x + get_random_float()) / float(cam.viewport.x);
                float v = float(y + get_random_float()) / float(cam.viewport.y);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(cam.samples);
            col = glm::sqrt(col);

            int output_index = x + size.x * y;
            output_buffer[output_index] = col;
        }
    }
}

int main() {
    unsigned int nx = 200;
    unsigned int ny = 100;
    unsigned int ns = 100;

    output_window window(nx * 3, ny * 3);

    glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin(0.0f);

    float R = (float)std::cos(M_PI / 4.0f);
    std::vector<hitable*> list;
    list.push_back(new sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(glm::vec3(0.8, 0.3, 0.3))));
    list.push_back(new sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(glm::vec3(0.8, 0.8, 0.0))));
    list.push_back(new sphere(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(glm::vec3(0.8, 0.6, 0.2), 0.0)));
    list.push_back(new sphere(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, new dialectric(1.5)));

    //list.push_back(new sphere(glm::vec3(-R, 0.0f, -1.0f), R, new lambertian(glm::vec3(0.0f, 0.0f, 1.0f))));
    //list.push_back(new sphere(glm::vec3( R, 0.0f, -1.0f), R, new lambertian(glm::vec3(1.0f, 0.0f, 0.0f))));

    hitable *world = new hitable_list(list);

    glm::vec3 lookfrom(3.0f, 3.0f, 2.0f);
    glm::vec3 lookat(0.0f, 0.0f, -1.0f);
    float dist_to_focus = glm::length(lookfrom - lookat);
    float aperture = 0.1f;

    camera cam(ns, glm::ivec2(nx, ny), lookfrom, lookat, glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, float(nx) / float(ny), aperture, dist_to_focus);

    std::vector<glm::vec3> rendered_image;
    rendered_image.reserve((unsigned long long int) (nx * ny));

    unsigned int num_threads = std::thread::hardware_concurrency();
    unsigned y_per_thread = ny / num_threads;
    double average_time = 0;
    for(int test = 0; test < 10; test++) {
        std::vector<std::thread> worker_threads;

        std::clock_t begin = std::clock();

        for(unsigned char i = 0; i < num_threads; i++) {
            worker_threads.push_back(
                    std::thread(
                            render_screen_part, glm::ivec2(0, y_per_thread * i), glm::ivec2(nx, y_per_thread * (i + 1)),
                            std::ref(cam), std::ref(world), std::ref(rendered_image)));
        }

        for(auto &thread : worker_threads) {
            thread.join();
        }

        std::clock_t end = std::clock();

        average_time += double(end - begin) / CLOCKS_PER_SEC;
    }
    average_time /= 10;

    std::cout << "Rendering completed in " << average_time << " seconds with " << num_threads << " threads\n";

    window.set_texture(rendered_image, nx, ny);
}