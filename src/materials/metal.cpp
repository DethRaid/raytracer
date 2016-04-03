//
// Created by David on 03-Apr-16.
//

#include "metal.h"
#include "../utils.h"

metal::metal(const vec3 &a, float r) : albedo(a) {
    if(r > 1) {
        r = 1;
    }

    roughness = r;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + roughness * random_in_unit_disk());
    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
}
