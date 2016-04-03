//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H


#include "material.h"
#include "textures/texture.h"

class lambertian : public material {
public:
    lambertian(texture * a) { albedo = a; }
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
    texture * albedo;
};


#endif //RAYTRACER_LAMBERTIAN_H
