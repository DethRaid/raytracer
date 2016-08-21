//
// Created by ddubois on 21-Aug-16.
//

#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center;
    // CLion complains about these lines, but it's wrong
    float a = glm::dot(r.direction(), r.direction());
    float b = 2.0 * glm::dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if(discriminant > 0.0f) {
        float temp = (-b - (float)sqrt(discriminant)) / (2.0f * a);
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }

        temp = (-b + (float)sqrt(discriminant)) / (2.0f * a);
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }

    return false;
}

