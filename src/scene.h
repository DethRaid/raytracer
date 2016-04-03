//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <vector>
#include "surfaces/surface.h"

class scene : public surface {
public:
    scene() {};
    scene(std::vector<surface *> l) {list = l;}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
private:
    std::vector<surface *> list;
};


#endif //RAYTRACER_SCENE_H
