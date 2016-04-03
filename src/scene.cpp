//
// Created by David on 03-Apr-16.
//

#include "scene.h"

bool scene::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(const hitable * s : list) {
        if(s->hit(r, t_min, t_max, temp_rec)) {
            if(temp_rec.t < closest_so_far) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
    }
    return hit_anything;
}