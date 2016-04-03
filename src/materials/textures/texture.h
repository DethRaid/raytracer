//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H


#include "../../vec3.h"

class texture {
public:
    virtual vec3 value(float u, float v, const vec3 &p) const = 0;
};


#endif //RAYTRACER_TEXTURE_H
