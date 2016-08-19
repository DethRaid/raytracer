//
// Created by David on 03-Apr-16.
//

#include "image_texture.h"

glm::vec3 image_texture::value(float u, float v, const glm::vec3 &p) const {
    int i = (int) (u * width);
    int j = (int) ((1 - v) * width - 0.001);

    if(i < 0) {
        i = 0;
    }
    if(j < 0) {
        j = 0;
    }

    if(i > width - 1) {
        i = width - 1;
    }
    if(j > height - 1) {
        j = height - 1;
    }

    float r = (float) (int(data[3 * i + 3 * width * j]) / 255.0);
    float g = (float) (int(data[3 * i + 3 * width * j + 1]) / 255.0);
    float b = (float) (int(data[3 * i + 3 * width * j + 2]) / 255.0);

    return glm::vec3(r, g, b);
}

