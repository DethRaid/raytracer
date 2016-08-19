//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_CONSTANT_TEXTURE_H
#define RAYTRACER_CONSTANT_TEXTURE_H


#include "texture.h"

class constant_texture : public texture {
public:
    constant_texture() {}
    constant_texture(glm::vec3 c) : color(c) {}
    virtual glm::vec3 value(float u, float v, const glm::vec3 &p) const {
        return color;
    }
private:
    glm::vec3 color;
};


#endif //RAYTRACER_CONSTANT_TEXTURE_H
