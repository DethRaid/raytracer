//
// Created by David on 03-Apr-16.
//

#include "pbr_material.h"
#include "../utils.h"

pbr_material::pbr_material(texture * albedo, texture * specular_color, texture * ior, float smoothness) {
    this->albedo = albedo;
    this->specular_color = specular_color;
    this->ior = ior;
    this->smoothness = smoothness;
}

bool pbr_material::scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const {
    glm::vec3 target = rec.hit_point + rec.normal + random_in_unit_disk();
    scattered = ray(rec.hit_point, target - rec.hit_point);
    attenuation = albedo->value(0, 0, rec.hit_point);

    // TODO: This function does not yet consider fresnel.
    return true;
}

bool pbr_material::refract(const ray &r_in, const hit_record &rec, float attenuation, ray &scattered, int color) const {
    glm::vec3 outward_normal;
    glm::vec3 reflected = reflect(r_in.direction(), rec.normal);
    glm::vec3 ni_over_nt;
    attenuation = 1;
    glm::vec3 refracted;
    float reflect_prob;
    glm::vec3 cosine;

    if(dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ior->value(rec.u, rec.t, rec.hit_point);
        cosine = ior->value(rec.u, rec.t, rec.hit_point) * glm::dot(glm::normalize(r_in.direction()), rec.normal);
    } else {
        outward_normal = rec.normal;
        ni_over_nt = (1.0f / ior->value(rec.u, rec.t, rec.hit_point));
        cosine = glm::vec3(-dot(r_in.direction(), rec.normal) / r_in.direction().length());
    }

    if(refract_ray(r_in.direction(), outward_normal, ni_over_nt[color], refracted)) {
        reflect_prob = schlick(cosine[color], ior->value(rec.u, rec.t, rec.hit_point)[color]);
    } else {
        reflect_prob = 1;
    }

    if(drand() < reflect_prob) {
        scattered = ray(rec.hit_point, reflected);
    } else {
        scattered = ray(rec.hit_point, refracted);
    }

    return true;
}



