//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../ray.h"
#include "../surfaces/hitable.h"

/*!
 * \brief A material to represent all the material parameters of a PBR hitable
 */
class material {
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};


#endif //RAYTRACER_MATERIAL_H
