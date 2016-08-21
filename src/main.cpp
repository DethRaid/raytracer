//
// Created by ddubois on 21-Aug-16.
//

#include <iostream>
#include <gl/glm/glm.hpp>
#include "ray.h"

float hit_sphere(const glm::vec3& center, float radius, const ray& r) {
    glm::vec3 oc = r.origin() - center;
    // CLion complains about these lines, but it's wrong
    float a = glm::dot(r.direction(), r.direction());
    float b = 2.0 * glm::dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if(discriminant < 0) {
        return -1.0f;
    } else {
        return (-b - (float)sqrt(discriminant)) / (2.0f * a);
    }
}

glm::vec3 color(const ray& r) {
    float t = hit_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);
    if(t > 0.0f) {
        glm::vec3 N = glm::normalize(r.point_at_parameter(t) - glm::vec3(0.0f, 0.0f, -1.0f));
        return N * 0.5f + 0.5f;
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin(0.0f);

    for(int j = ny - 1; j >= 0; j--) {
        for(int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            glm::vec3 col = color(r);

            int ir = int(255.99 * col.r);
            int ig = int(255.99 * col.g);
            int ib = int(255.99 * col.b);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}