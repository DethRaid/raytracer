//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <random>
#include <GL/glm/glm.hpp>

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

bool refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted) {
    glm::vec3 uv = glm::normalize(v);
    float dt = glm::dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if(discriminant > 0) {
        refracted = ni_over_nt * (v - n * dt) - n * (float)sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * (float)pow((1.0f - cosine), 5.0f);
}

#endif //RAYTRACER_UTILS_H
