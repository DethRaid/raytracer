//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_DIALECTRIC_H
#define RAYTRACER_DIALECTRIC_H

#include "material.h"
#include "../utils.h"

class dialectric : public material {
public:
    dialectric(float ri) : ref_idx(ri) {};
    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const {
        glm::vec3 reflected = glm::reflect(r_in.direction(), rec.normal);
        attenuation = glm::vec3(1.0f, 1.0f, 0.0f);

        glm::vec3 outward_normal;
        float ni_over_nt;
        float cosine;

        if(glm::dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * glm::dot(r_in.direction(), rec.normal) / glm::length(r_in.direction());

        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -glm::dot(r_in.direction(), rec.normal) / glm::length(r_in.direction());
        }

        glm::vec3 refracted;
        float reflect_prob;
        if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            scattered = ray(rec.p, reflected);
            reflect_prob = 1.0;
        }

        if(get_random_float() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }

        return true;
    }

    float ref_idx;
};

#endif //RAYTRACER_DIALECTRIC_H
