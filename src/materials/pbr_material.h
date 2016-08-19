//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_PBR_MATERIAL_H
#define RAYTRACER_PBR_MATERIAL_H

#include "../ray.h"
#include "../surfaces/hitable.h"
#include "textures/texture.h"

class pbr_material {

    /*!
     * \brief Initializes a material with some basic PBR parameters
     *
     * \param albedo The material's albedo, split into RGB
     * \param ior The material's index of refraction, split into RGB
     * \param smoothness How smooth the hitable of the material is
     */
    pbr_material(texture * albedo, texture * specular_color, texture * ior, float smoothness);

    /*!
     * \brief Calculates diffuse/SSS reflection for the material
     *
     * \param r_in The ray that hit the hitable
     * \param rec The position and normal where the ray hit the hitable
     * \param attenuation The attenuation color of the ray
     * \param scattered The ray that scatters away from this hitable
     */
    virtual bool scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const;

    /*!
     * \brief Calculated the refraction/reflection ray from the hitable
     *
     * \param r_in The ray that hit the hitable
     * \param hit_record The position and normal where the ray hit the hitable
     * \param attenuation The attenuation color of the ray
     * \param scattered The refracted ray
     * \param color Which color to calcualte refraction for. Should be 0 for red, 1 for green, and 2 for blue
     */
    virtual bool refract(const ray &r_in, const hit_record &rec, float attenuation, ray &scattered, int color) const;

private:
    texture * ior;
    float smoothness;
    texture * albedo;
    texture * specular_color;
};


#endif //RAYTRACER_PBR_MATERIAL_H
