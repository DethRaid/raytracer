//
// Created by ddubois on 21-Aug-16.
//

#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center;
    float a = glm::dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc);
    float discriminant = b * b - a * c;

    if(discriminant > 0.0f) {
        float temp = (-b - (float)sqrt(b * b - a * c)) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }

        temp = (-b + (float)sqrt(b * b - a * c)) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }

    return false;
}

