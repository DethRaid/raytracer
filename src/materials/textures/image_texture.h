//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_IMAGE_TEXTURE_H
#define RAYTRACER_IMAGE_TEXTURE_H


#include "texture.h"

class image_texture : public texture {
public:
    image_texture() {}
    image_texture(unsigned char * pixels, int image_width, int image_height) : data(pixels), width(image_width), height(image_height) {}
    virtual glm::vec3 value(float u, float v, const glm::vec3 &p) const;
private:
    unsigned char *data;
    int width, height;
};


#endif //RAYTRACER_IMAGE_TEXTURE_H
