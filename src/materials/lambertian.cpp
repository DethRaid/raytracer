//
// Created by David on 03-Apr-16.
//

#include "lambertian.h"
#include "../utils.h"

bool lambertian::scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const {
    glm::vec3 target = rec.hit_point + rec.normal + random_in_unit_disk();
    scattered = ray(rec.hit_point, target - rec.hit_point);
    attenuation = albedo->value(rec.u, rec.t, rec.hit_point);
    return true;
}
