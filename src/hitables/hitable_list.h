//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_HITABLE_LIST_H
#define RAYTRACER_HITABLE_LIST_H

#include <vector>
#include <c++/memory>

#include "hitable.h"

class hitable_list : public hitable {
public: hitable_list() {}
    hitable_list(std::vector<hitable*>& l) : list(l) {};
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    std::vector<hitable*> list;
};

#endif //RAYTRACER_HITABLE_LIST_H
