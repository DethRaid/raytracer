//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_HITABLE_LIST_H
#define RAYTRACER_HITABLE_LIST_H

#include "hitable.h"

class hitable_list : public hitable {
public: hitable_list() {}
    hitable_list(hitable **l, int n) { list = l; list_size = n; };
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    // We don't need no stinkin' cache coherency!
    hitable **list;
    int list_size;
};

#endif //RAYTRACER_HITABLE_LIST_H
