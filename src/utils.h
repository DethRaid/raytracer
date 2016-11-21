//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include "3rdparty/glm/glm/glm.hpp"
#include "bvh/aabb.h"

float get_random_float();

glm::vec3 random_in_unit_sphere();

glm::vec3 random_in_unit_disk();

bool refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted);

float schlick(float cosine, float ref_idx);

aabb surrounding_box(aabb box0, aabb box1);

int box_x_compare(const void * a, const void * b);

int box_y_compare(const void * a, const void * b);

int box_z_compare(const void * a, const void * b);

#endif //RAYTRACER_UTILS_H
