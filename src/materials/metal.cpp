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

bool metal::scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const {
    glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
    scattered = ray(rec.hit_point, reflected + roughness * random_in_unit_disk());

    float cosine = dot(reflected, rec.normal);

    attenuation = fresnel(cosine, specular_color->value(rec.u, rec.t, rec.hit_point));
    return dot(scattered.direction(), rec.normal) > 0;
}
