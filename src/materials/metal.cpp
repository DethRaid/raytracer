//
// Created by David on 03-Apr-16.
//

#include "metal.h"
#include "../utils.h"

metal::metal(texture * a, float r) {
    if(r > 1) {
        r = 1;
    }

    roughness = r;

    specular_color = a;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + roughness * random_in_unit_disk());

    float cosine = dot(reflected, rec.normal);

    attenuation = fresnel(cosine, specular_color->value(0, 0, rec.p));
    return dot(scattered.direction(), rec.normal) > 0;
}
