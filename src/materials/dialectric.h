//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_DIALECTRIC_H
#define RAYTRACER_DIALECTRIC_H


#include "material.h"

class dialectric : public material {
public:
    dialectric(float ri);
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;

private:
    float n;
};


#endif //RAYTRACER_DIALECTRIC_H
