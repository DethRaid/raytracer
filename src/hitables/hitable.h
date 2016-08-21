//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_HITABLE_H
#define RAYTRACER_HITABLE_H

#include "../ray.h"

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record &rec) const = 0;
};


#endif //RAYTRACER_HITABLE_H
