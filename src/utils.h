//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <cstdlib>
#include "vec3.h"
#include "bvh/aabb.h"

#define PI 3.14159265

float drand();

vec3 random_in_unit_disk();

vec3 reflect(const vec3 &v, const vec3 &n);

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);

float schlick(float cosine, float n);

vec3 fresnel(float cosine, vec3 n);

aabb surrounding_box(const aabb & box0, const aabb & box1);

#endif //RAYTRACER_UTILS_H
