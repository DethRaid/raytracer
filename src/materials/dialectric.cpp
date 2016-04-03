//
// Created by David on 03-Apr-16.
//

#include "dialectric.h"
#include "../utils.h"

dialectric::dialectric(float ri) : n(ri) { }

bool dialectric::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1);
    vec3 refracted;
    float reflect_prob;
    float cosine;

    if(dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = n;
        cosine = n * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = (float) (1.0 / n);
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, n);
    } else {
        reflect_prob = 1;
    }

    if(drand() < reflect_prob) {
        scattered = ray(rec.p, reflected);
    } else {
        scattered = ray(rec.p, refracted);
    }

    return true;
}



