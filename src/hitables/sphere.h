//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "hitable.h"

class sphere : public hitable {
public:
    sphere() {};
    sphere(glm::vec3 cen, float r) : center(cen), radius(r) {};
    virtual bool hit(const ray& r, float _tmin, float t_max, hit_record& rec) const;

    glm::vec3 center;
    float radius;
};

#endif //RAYTRACER_SPHERE_H
