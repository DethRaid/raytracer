//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "vec3.h"
#include "ray.h"

class camera {
public:
    camera() : lower_left_corner(-2, -1, -1), horizontal(4, 0, 0), vertical(0, 2, 0), origin(0) {}

    ray get_ray(float u, float v);
private:
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
};


#endif //RAYTRACER_CAMERA_H
