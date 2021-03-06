/*!
 * \brief
 *
 * \author ddubois 
 * \date 22-Nov-16.
 */

#include "aabb.h"
#include <algorithm>

bool aabb::hit(const ray &r, float tmin, float tmax) const {
    for(int a = 0; a < 3; a++) {
        float invD = 1.0f / r.direction()[a];
        float t0 = (min[a] - r.origin()[a]) * invD;
        float t1 = (max[a] - r.origin()[a]) * invD;
        if(invD < 0.0f) {
            std::swap(t0, t1);
        }
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;
        if(tmax <= tmin) {
            return false;
        }
    }
    return true;
}

std::vector<glm::vec3> aabb::get_wireframe()  {
    std::vector<glm::vec3> vertices;

    vertices.push_back(min);
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, min.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(min.x, max.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, max.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(min.x, min.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, min.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(min.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));


    vertices.push_back(min);
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(min.x, max.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(max.x, min.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, max.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(min.x, min.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(min.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(max.x, min.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));


    vertices.push_back(min);
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(min.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(max.x, min.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, min.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(min.x, max.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(min.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    vertices.push_back(glm::vec3(max.x, max.y, min.z));
    vertices.push_back(glm::vec3(0, 1, 0));
    vertices.push_back(glm::vec3(max.x, max.y, max.z));
    vertices.push_back(glm::vec3(0, 1, 0));

    return vertices;
}
