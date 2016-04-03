//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "hitable.h"

class sphere : public hitable {
public:
    sphere() {}
    sphere(vec3 cent, float r, material *surface_material) : center(cent), radius(r) {
        mat = surface_material;
    }
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;
private:
    vec3 center;
    float radius;
};


#endif //RAYTRACER_SPHERE_H
