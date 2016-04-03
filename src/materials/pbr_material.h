//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_PBR_MATERIAL_H
#define RAYTRACER_PBR_MATERIAL_H

#include "material.h"

class pbr_material : public material {

    /*!
     * \brief Initializes a material with some basic PBR parameters
     *
     * \param albedo The material's albedo, split into RGB
     * \param ior The material's index of refraction, split into RGB
     * \param smoothness How smooth the surface of the material is
     */
    pbr_material(vec3 albedo, vec3 specular_color, vec3 ior, float smoothness);

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
    vec3 ior;
    float smoothness;
    vec3 albedo;
    vec3 specular_color;
};


#endif //RAYTRACER_PBR_MATERIAL_H
