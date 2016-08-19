//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H


#include <gl/glm/glm.hpp>

class texture {
public:
    virtual glm::vec3 value(float u, float v, const glm::vec3 &p) const = 0;
};


#endif //RAYTRACER_TEXTURE_H
