//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <vector>
#include "surfaces/hitable.h"

class scene : public hitable {
public:
    scene() {};
    scene(std::vector<hitable *> l) {list = l;}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
private:
    std::vector<hitable *> list;
};


#endif //RAYTRACER_SCENE_H
