//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "vec3.h"
#include "ray.h"

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float fov, float aspect, float aperature, float focus_dist);

    ray get_ray(float u, float v);
private:
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
    float lens_radius;
};


#endif //RAYTRACER_CAMERA_H
