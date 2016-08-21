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

#endif //RAYTRACER_UTILS_H
