/*!
 * \brief
 *
 * \author ddubois 
 * \date 13-Nov-16.
 */

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "../3rdparty/glm/glm/glm.hpp"
#include "../ray.h"
#include <vector>

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class aabb {
public:
    aabb() {}
    aabb(const glm::vec3& a, const glm::vec3& b) : min(a), max(b) {}

    bool hit(const ray &r, float tmin, float tmax) const;

    std::vector<glm::vec3> get_wireframe();

    glm::vec3 min, max;
};

#endif //RAYTRACER_AABB_H
