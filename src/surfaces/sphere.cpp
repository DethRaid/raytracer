//
// Created by David on 03-Apr-16.
//

#include "sphere.h"
#include "../utils.h"

void get_sphere_uv(const glm::vec3 &p, float &u, float &v) {
    float phi = atan2(p.z, p.x);
    float theta = asin(p.y);
    u = 1 - (phi + PI) / (2 * PI);
    v = (theta + PI / 2) / PI;
}

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    glm::vec3 oc = r.origin() - center;
    float a = glm::dot(r.direction(), r.direction());
    float b = glm::dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if(discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        rec.t = temp;
        rec.hit_point = r.point_at_parameter(temp);
        rec.normal = (rec.hit_point - center) / radius;
        rec.mat = mat;
        get_sphere_uv(rec.hit_point, rec.u, rec.v);
        if(temp < t_max && temp > t_min) {
            // The hit position is within the allowed ray range
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;
        rec.t = temp;
        // Check if the ray hit the back face of the sphere
        if(temp < t_max && temp > t_min) {
            return true;
        }
    }

    return false;
}

bool sphere::bounding_box(float t0, float t1, aabb &box) const {
    box = aabb(center - radius, center + radius);
    return true;
}

