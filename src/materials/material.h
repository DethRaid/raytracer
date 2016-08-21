//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "../ray.h"
#include "../hitables/hitable.h"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const = 0;
};

#endif //RAYTRACER_MATERIAL_H
