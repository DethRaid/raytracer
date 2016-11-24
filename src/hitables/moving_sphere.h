#include <math.h>
#include "hitable.h"

/*!
 * \brief
 *
 * \author ddubois 
 * \date 13-Nov-16.
 */

#ifndef RAYTRACER_MOVING_SPHERE_H
#define RAYTRACER_MOVING_SPHERE_H

#include "../materials/material.h"

class moving_sphere : public hitable {
public:
    moving_sphere() {};
    moving_sphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, material *m) : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {};

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record &rec) const;
    virtual bool compute_bounding_box(float t0, float t1, aabb& box) const;
    virtual std::vector<glm::vec3> get_wireframe();
    glm::vec3 center(float time) const;

    glm::vec3 center0, center1;
    float time0, time1;
    float radius;
    material *mat_ptr;
};

#endif //RAYTRACER_MOVING_SPHERE_H
