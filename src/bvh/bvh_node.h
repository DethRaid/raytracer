//
// Created by David on 03-Apr-16.
//

#ifndef RAYTRACER_BVH_NODE_H
#define RAYTRACER_BVH_NODE_H


#include <vector>
#include "../surfaces/hitable.h"

class bvh_node : public hitable {
public:
    bvh_node() {}
    bvh_node(std::vector<hitable *> list, float time0, float time1);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;
private:
    hitable * left;
    hitable * right;
    aabb box;
};


#endif //RAYTRACER_BVH_NODE_H
