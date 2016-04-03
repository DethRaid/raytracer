//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H


#include "../vec3.h"
#include "../ray.h"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat;
};

class surface {
public:
    /*!
     * \brief Determines if a given ray hits this surface.
     *
     * \param r The ray to check for intersection with
     * \param t_min The minimum allowed ray parameter t
     * \param t_max The maximum allowed ray parameter t
     * \param rec The hit_record to output hit information with. I expect this struct to grow considerably
     */
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
protected:
    material *mat;
};


#endif //RAYTRACER_SURFACE_H
