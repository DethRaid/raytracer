//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "ray.h"

class camera {
public:
    camera() : lower_left_corner(-2.0f, -1.0f, -1.0f),
               horizontal(4.0f, 0.0f, 0.0f),
               vertical(0.0f, 2.0f, 0.0f),
               origin(0.0f, 0.0f, 0.0f)
    {}

    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); };

    glm::vec3 lower_left_corner;
    glm::vec3 origin;
    glm::vec3 horizontal;
    glm::vec3 vertical;
};


#endif //RAYTRACER_CAMERA_H
