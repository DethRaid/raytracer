//
// Created by David on 03-Apr-16.
//

#include "sphere.h"

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if(discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        if(temp < t_max && temp > t_min) {
            // The hit position is within the allowed ray range
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;
        // Check if the ray hit the back face of the sphere
        if(temp < t_max && temp > t_min) {
            // The hit position is within the allowed ray range
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }

    return false;
}