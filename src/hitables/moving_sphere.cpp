/*!
 * \brief
 *
 * \author ddubois 
 * \date 22-Nov-16.
 */

#include <math.h>
#include "moving_sphere.h"
#include "../utils.h"

glm::vec3 moving_sphere::center(float time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center(r.time);
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
            rec.normal = (rec.p - center(r.time)) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / (2.0f * a);
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time)) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

bool moving_sphere::compute_bounding_box(float t0, float t1, aabb &box) const {
    aabb box0 = aabb(center(t0) - glm::vec3(radius), center(t0) + glm::vec3(radius));
    aabb box1 = aabb(center(t1) - glm::vec3(radius), center(t1) + glm::vec3(radius));

    box = surrounding_box(box0, box1);

    return true;
}

std::vector<glm::vec3> moving_sphere::get_wireframe() {
    // Like with sphere, but make one wireframe for the two extremes of motion
    // If I was super cool, I'd make the spheres connected
    // I'm not super cool
    // Build three circles, each aligned with one of the cardinal directions
    auto buffer = std::vector<glm::vec3>{};

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.x = std::sin(i) * radius;
        vec.y = std::cos(i) * radius;
        buffer.push_back(vec + center(time0));
        buffer.push_back(mat_ptr->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.x = std::sin(i) * radius;
        vec.z = std::cos(i) * radius;
        buffer.push_back(vec + center(time0));
        buffer.push_back(mat_ptr->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.z = std::sin(i) * radius;
        vec.y = std::cos(i) * radius;
        buffer.push_back(vec + center(time0));
        buffer.push_back(mat_ptr->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.x = std::sin(i) * radius;
        vec.y = std::cos(i) * radius;
        buffer.push_back(vec + center(time1));
        buffer.push_back(mat_ptr->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.x = std::sin(i) * radius;
        vec.z = std::cos(i) * radius;
        buffer.push_back(vec + center(time1));
        buffer.push_back(mat_ptr->get_color());
    }

    for(float i = 0; i < M_PI * 2; i += (M_PI * 2) / 16.0) {
        glm::vec3 vec;
        vec.z = std::sin(i) * radius;
        vec.y = std::cos(i) * radius;
        buffer.push_back(vec + center(time1));
        buffer.push_back(mat_ptr->get_color());
    }

    return buffer;
}


