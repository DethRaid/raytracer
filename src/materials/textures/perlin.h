//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_PERLIN_H
#define RAYTRACER_PERLIN_H


#include "../../vec3.h"

class perlin {
public:
    float noise(const vec3 &p) const;
    static float *ranfloat;
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;
};


#endif //RAYTRACER_PERLIN_H
