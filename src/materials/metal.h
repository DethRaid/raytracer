//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H


#include "material.h"

class metal : public material {
public:
    metal(const vec3 &a, float r);
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
    vec3 albedo;
    float roughness;
};


#endif //RAYTRACER_METAL_H
