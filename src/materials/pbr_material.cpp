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

bool pbr_material::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 target = rec.p + rec.normal + random_in_unit_disk();
    scattered = ray(rec.p, target - rec.p);
    attenuation = albedo->value(0, 0, rec.p);

    // TODO: This function does not yet consider fresnel.
    return true;
}

bool pbr_material::refract(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    /*vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    vec3 ni_over_nt;
    attenuation = vec3(1);
    vec3 refracted;
    float reflect_prob;
    vec3 cosine;

    if(dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ior;
        cosine = ior * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = (float) (1.0 / ior);
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ior);
    } else {
        reflect_prob = 1;
    }

    if(drand() < reflect_prob) {
        scattered = ray(rec.p, reflected);
    } else {
        scattered = ray(rec.p, refracted);
    }

    return true;*/

    return false;
}



