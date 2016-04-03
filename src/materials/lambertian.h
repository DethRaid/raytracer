//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H


#include "material.h"

class lambertian : public material {
public:
    lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
    vec3 albedo;
};


#endif //RAYTRACER_LAMBERTIAN_H
