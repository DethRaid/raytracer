/*!
 * \brief Defines a bunch of useful utility functions
 *
 * \author ddubois 
 * \date 13-Nov-16.
 */

#include "utils.h"
#include "hitables/hitable.h"
#include <random>
#include <iostream>

float get_random_float() {
    static std::random_device rd;

    return float(rd()) / float(rd.max());
}

glm::vec3 random_in_unit_sphere() {
    glm::vec3 p;
    do {
        p = glm::vec3(get_random_float(), get_random_float(), get_random_float()) * 2.0f - 1.0f;
        // CLion, Y U NO PARSE TEMPLATES RIGHT?
    } while(glm::length(p) >= 1.0f);
    return p;
}

glm::vec3 random_in_unit_disk() {
    glm::vec3 p;
    do {
        p = glm::vec3(get_random_float(), get_random_float(), 0.0f) * 2.0f - glm::vec3(1.0f, 1.0f, 0.0f);
        // CLion, Y U NO PARSE TEMPLATES RIGHT?
    } while(glm::dot(p, p) >= 1.0f);
    return p;
}

bool refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted) {
    glm::vec3 uv = glm::normalize(v);
    float dt = glm::dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if(discriminant > 0) {
        refracted = ni_over_nt * (v - n * dt) - n * (float)std::sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * (float)std::pow((1.0f - cosine), 5.0f);
}

aabb surrounding_box(aabb box0, aabb box1) {
    glm::vec3 small(glm::min(box0.min, box1.min));
    glm::vec3 big(glm::min(box0.max, box1.max));

    return aabb(small, big);
}

int box_x_compare(const void * a, const void * b) {
    aabb box_left, box_right;
    hitable *ah = *(hitable**)a;
    hitable *bh = *(hitable**)b;
    if(!ah->compute_bounding_box(0, 0, box_left) || !bh->compute_bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box could be constructed";
    }

    if(box_left.min.x - box_right.min.x < 0) {
        return -1;
    } else {
        return 1;
    }
}

int box_y_compare(const void * a, const void * b) {
    aabb box_left, box_right;
    hitable *ah = *(hitable**)a;
    hitable *bh = *(hitable**)b;
    if(!ah->compute_bounding_box(0, 0, box_left) || !bh->compute_bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box could be constructed";
    }

    if(box_left.min.y - box_right.min.y < 0) {
        return -1;
    } else {
        return 1;
    }
}

int box_z_compare(const void * a, const void * b) {
    aabb box_left, box_right;
    hitable *ah = *(hitable**)a;
    hitable *bh = *(hitable**)b;
    if(!ah->compute_bounding_box(0, 0, box_left) || !bh->compute_bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box could be constructed";
    }

    if(box_left.min.z - box_right.min.z < 0) {
        return -1;
    } else {
        return 1;
    }
}
