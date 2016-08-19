//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <cstdlib>
#include <gl/glm/glm.hpp>
#include "bvh/aabb.h"

#define PI 3.14159265

float drand();

glm::vec3 random_in_unit_disk();

glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n);

bool refract_ray(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nt, glm::vec3 &refracted);

float schlick(float cosine, float n);

glm::vec3 fresnel(float cosine, glm::vec3 n);

aabb surrounding_box(const aabb & box0, const aabb & box1);

#endif //RAYTRACER_UTILS_H
