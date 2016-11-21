//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_HITABLE_H
#define RAYTRACER_HITABLE_H

#include "../ray.h"
#include "../bvh/aabb.h"

class material;

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    material* mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record &rec) const = 0;
    virtual bool compute_bounding_box(float t0, float t1, aabb &box) const = 0;

    /*!
     * \brief Constructs the vertex buffer to draw this hitable thing as a wireframe
     *
     * I don't like this being here because it feels like hitables are only concerned with being hit by rays, and this
     * method exists to support debugging through OpenGL, which is a completely separate concern. However, this is the
     * best way I know of to accomplish what I want (separate wireframe construction logic for each type of hitable
     * thing
     */
    virtual std::vector<glm::vec3> get_wireframe() = 0;
};


#endif //RAYTRACER_HITABLE_H
