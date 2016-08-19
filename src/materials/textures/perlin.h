//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_PERLIN_H
#define RAYTRACER_PERLIN_H


#include <gl/glm/glm.hpp>

class perlin {
public:
    float noise(const glm::vec3 &p) const;
    static float *ranfloat;
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;
};


#endif //RAYTRACER_PERLIN_H
