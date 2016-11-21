//
// Created by ddubois on 21-Aug-16.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "hitable.h"

class sphere : public hitable {
public:
    sphere() {};
    sphere(glm::vec3 cen, float r, material* mat) : center(cen), radius(r), mat(mat) {};
    virtual bool hit(const ray& r, float _tmin, float t_max, hit_record& rec) const;
    virtual bool compute_bounding_box(float t0, float t1, aabb &box) const;
    virtual std::vector<glm::vec3> get_wireframe();

    glm::vec3 center;
    float radius;
    material* mat;
};

#endif //RAYTRACER_SPHERE_H
