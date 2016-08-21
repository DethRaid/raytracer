//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "material.h"
#include "../utils.h"

class metal : public material {
public:
    metal(const glm::vec3& c, float r) : color(c), roughness(r) {};
    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const {
        glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + roughness * random_in_unit_sphere());
        attenuation = color;
        return glm::dot(scattered.direction(), rec.normal) > 0.0f;
    }

    glm::vec3 color;
    float roughness;
};

#endif //RAYTRACER_METAL_H
