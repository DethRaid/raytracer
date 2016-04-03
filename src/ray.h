//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const vec3 &origin, const vec3 &direction, float ti = 0.0) { this->orig = origin; this->dir = direction;}
    vec3 origin() const {return orig;}
    vec3 direction() const {return dir;}
    vec3 point_at_parameter(float t) const {return orig + dir * t;}

private:
    vec3 orig;
    vec3 dir;
};


#endif //RAYTRACER_RAY_H
