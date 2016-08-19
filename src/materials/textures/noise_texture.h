//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_NOISE_TEXTURE_H
#define RAYTRACER_NOISE_TEXTURE_H


#include "texture.h"
#include "perlin.h"

class noise_texture : public texture {
public:
    noise_texture() {}
    virtual glm::vec3 value(float u, float v, const glm::vec3 &p) const {
        return glm::vec3(1) * noise.noise(p);
    }
private:
    perlin noise;
};


#endif //RAYTRACER_NOISE_TEXTURE_H
