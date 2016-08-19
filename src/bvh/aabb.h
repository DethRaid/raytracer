//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include <gl/glm/glm.hpp>
#include "../ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

/*!
 * \brief Represents an Axis-Aligned Bounding Box
 */
class aabb {
public:
    aabb() {}
    aabb(const glm::vec3 &a, const glm::vec3 &b) { _min = a; _max = b; }
    glm::vec3 min() const { return _min; }
    glm::vec3 max() const { return _max; }

    bool hit(const ray &r, float tmin, float tmax) const;

private:
    glm::vec3 _min;
    glm::vec3 _max;
};


#endif //RAYTRACER_AABB_H
