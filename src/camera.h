//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "ray.h"

class camera {
public:
    camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float fov, float aspect, float aperature, float focus_dist);

    ray get_ray(float u, float v);
private:
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 origin;
    float lens_radius;
};


#endif //RAYTRACER_CAMERA_H
