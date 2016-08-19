//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <gl/glm/glm.hpp>

class ray {
public:
    ray() {}
    ray(const glm::vec3 &origin, const glm::vec3 &direction, float ti = 0.0) { this->orig = origin; this->dir = direction;}
    glm::vec3 origin() const {return orig;}
    glm::vec3 direction() const {return dir;}
    glm::vec3 point_at_parameter(float t) const {return orig + dir * t;}

private:
    glm::vec3 orig;
    glm::vec3 dir;
};


#endif //RAYTRACER_RAY_H
