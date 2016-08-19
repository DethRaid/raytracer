//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_CHECKER_TEXTURE_H
#define RAYTRACER_CHECKER_TEXTURE_H


#include "textures/texture.h"

class checker_texture : public texture {
public:
    checker_texture() {}
    checker_texture(texture *t0, texture *t1) : even(t0), odd(t1) {}

    virtual glm::vec3 value(float u, float v, const glm::vec3 &p) const;
private:
    texture * odd;
    texture * even;
};


#endif //RAYTRACER_CHECKER_TEXTURE_H
