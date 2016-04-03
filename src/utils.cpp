//
// Created by David on 03-Apr-16.
//

#include "utils.h"

float drand()  {
    return rand() / static_cast<float>(RAND_MAX);
}

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand(), drand(), drand()) - vec3(1);
    } while(p.squared_length() >= 1.0);

    return p;
}

vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = (float) (1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt));
    if(discriminant > 0) {
        refracted = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);
        return true;
    }

    return false;
}

float schlick(float cosine, float n) {
    float r0 = (1 - n) / (1 + n);
    r0 = r0 * r0;
    return (float) (r0 + (1 - r0) * pow((1 - cosine), 5));
}

vec3 fresnel(float cosine, vec3 n) {
    return n + (1 - n) * pow((1 - cosine), 5);
}

aabb surrounding_box(const aabb & box0, const aabb & box1) {
    vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));

    vec3 big(fmax(box0.max().x(), box1.max().x()),
             fmax(box0.max().y(), box1.max().y()),
             fmax(box0.max().z(), box1.max().z()));

    return aabb(small, big);
}
