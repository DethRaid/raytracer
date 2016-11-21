/*!
 * \brief
 *
 * \author ddubois 
 * \date 13-Nov-16.
 */

#ifndef RAYTRACER_BVH_NODE_H
#define RAYTRACER_BVH_NODE_H

#include <vector>
#include <iostream>
#include "hitable.h"
#include "../utils.h"

class bvh_node : public hitable {
    public:
    bvh_node() {};
    bvh_node(hitable ** l, int n, float time0, float time1);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record &rec) const;
    virtual bool compute_bounding_box(float t0, float t1, aabb &box) const;
    virtual std::vector<glm::vec3> get_wireframe();

    hitable *left;
    hitable *right;

    aabb box;
};

#endif //RAYTRACER_BVH_NODE_H
