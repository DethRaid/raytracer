//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <cstdlib>
#include "vec3.h"

#define PI 3.14159265

float drand();

vec3 random_in_unit_disk();

vec3 reflect(const vec3 &v, const vec3 &n);

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);

float schlick(float cosine, float n);

#endif //RAYTRACER_UTILS_H
