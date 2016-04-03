//
// Created by David on 03-Apr-16.
//

#include "pbr_material.h"

pbr_material::pbr_material(vec3 albedo, vec3 specular_color, vec3 ior, float smoothness) {
    this->albedo = albedo;
    this->specular_color = specular_color;
    this->ior = ior;
    this->smoothness = smoothness;
}

bool pbr_material::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    return false;
}

