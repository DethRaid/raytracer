//
// Created by ddubois on 21-Aug-16.
//

#include <math.h>
#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center;
    // CLion complains about these lines, but it's wrong
    float a = glm::dot(r.direction(), r.direction());
    float b = 2.0 * glm::dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if(discriminant > 0.0f) {
        float temp = (-b - std::sqrt(discriminant)) / (2.0f * a);
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / (2.0f * a);
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

bool sphere::compute_bounding_box(float t0, float t1, aabb &box) const {
    box = aabb(center - glm::vec3(radius), center + glm::vec3(radius));
    return true;
}

std::vector<glm::vec3> sphere::get_wireframe() {
    // Build three circles, each aligned with one of the cardinal directions
    auto buffer = std::vector<glm::vec3>{};

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.x = std::sin(i) * radius;
        vec.y = std::cos(i) * radius;
        buffer.push_back(vec + center);
        buffer.push_back(mat->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.x = std::sin(i) * radius;
        vec.z = std::cos(i) * radius;
        buffer.push_back(vec + center);
        buffer.push_back(mat->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.z = std::sin(i) * radius;
        vec.y = std::cos(i) * radius;
        buffer.push_back(vec + center);
        buffer.push_back(mat->get_color());
    }

    return buffer;
}

