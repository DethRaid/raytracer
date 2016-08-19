//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H


#include "material.h"
#include "textures/texture.h"

class metal : public material {
public:
    metal(texture * a, float r);
    virtual bool scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const;

private:
    texture * specular_color;
    float roughness;
};


#endif //RAYTRACER_METAL_H
