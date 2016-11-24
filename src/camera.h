//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "ray.h"

class camera {
public:
    camera(unsigned samples,
           glm::ivec2 viewport, glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup,
           float vfov, float aspect, float aperture, float focus_dist,
           float t0, float t1);

    ray get_ray(float s, float t);

    glm::vec3 get_position();
    glm::vec3 get_look_target();
    glm::vec3 get_up();

    glm::vec3 lower_left_corner;
    glm::vec3 origin;
    glm::vec3 look_target;
    glm::vec3 up;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 u, v, w;
    glm::ivec2 viewport;
    float lens_radius;
    unsigned samples;

    float time0, time1;
};


#endif //RAYTRACER_CAMERA_H
