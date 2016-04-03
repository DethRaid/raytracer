//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "../vec3.h"
#include "../ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

/*!
 * \brief Represents an Axis-Aligned Bounding Box
 */
class aabb {
public:
    aabb() {}
    aabb(const vec3 &a, const vec3 &b) { _min = a; _max = b; }
    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool hit(const ray &r, float tmin, float tmax) const;

private:
    vec3 _min;
    vec3 _max;
};


#endif //RAYTRACER_AABB_H
