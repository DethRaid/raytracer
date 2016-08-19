//
// Created by David on 03-Apr-16.
//

#include "utils.h"

float drand()  {
    return rand() / static_cast<float>(RAND_MAX);
}

glm::vec3 random_in_unit_disk() {
    glm::vec3 p;
    do {
        p = glm::vec3(drand(), drand(), drand()) * glm::vec3(2.0) - glm::vec3(1);
    } while(p.length() >= 1.0);

    return p;
}

glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

bool refract_ray(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nt, glm::vec3 &refracted) {
    glm::vec3 uv = glm::normalize(v);
    float dt = glm::dot(uv, n);
    float discriminant = (float) (1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt));
    if(discriminant > 0) {
        refracted = ni_over_nt * (v - n * glm::vec3(dt)) - n * static_cast<float>(sqrt(discriminant));
        return true;
    }

    return false;
}

float schlick(float cosine, float n) {
    float r0 = (1 - n) / (1 + n);
    r0 = r0 * r0;
    return (float) (r0 + (1 - r0) * pow((1 - cosine), 5));
}

glm::vec3 fresnel(float cosine, glm::vec3 n) {
    return n + (glm::vec3(1) - n) * static_cast<float>(pow((1 - cosine), 5));
}

aabb surrounding_box(const aabb & box0, const aabb & box1) {
    glm::vec3 small(fmin(box0.min().x, box1.min().x),
                    fmin(box0.min().y, box1.min().y),
                    fmin(box0.min().z, box1.min().z));

    glm::vec3 big(fmax(box0.max().x, box1.max().x),
                  fmax(box0.max().y, box1.max().y),
                  fmax(box0.max().z, box1.max().z));

    return aabb(small, big);
}
