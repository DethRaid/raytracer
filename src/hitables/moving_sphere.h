 #include "hitable.h"

/*!
 * \brief
 *
 * \author ddubois 
 * \date 13-Nov-16.
 */

#ifndef RAYTRACER_MOVING_SPHERE_H
#define RAYTRACER_MOVING_SPHERE_H


class moving_sphere : public hitable {
public:
    moving_sphere() {};
    moving_sphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, material *m) : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {};

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record &rec) const;
    virtual bool compute_bounding_box(float t0, float t1, aabb& box) const;
    glm::vec3 center(float time) const;

    glm::vec3 center0, center1;
    float time0, time1;
    float radius;
    material *mat_ptr;
};

glm::vec3 moving_sphere::center(float time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

 bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
     glm::vec3 oc = r.origin() - center(r.time);
     // CLion complains about these lines, but it's wrong
     float a = glm::dot(r.direction(), r.direction());
     float b = 2.0 * glm::dot(oc, r.direction());
     float c = glm::dot(oc, oc) - radius * radius;
     float discriminant = b * b - 4 * a * c;

     if(discriminant > 0.0f) {
         float temp = (-b - std::sqrt(discriminant)) / (2.0f * a);
         if(temp < t_max && temp > t_min) {
             rec.t = temp;
             rec.p = r.point_at_parameter(rec.t);
             rec.normal = (rec.p - center(r.time)) / radius;
             rec.mat_ptr = mat_ptr;
             return true;
         }

         temp = (-b + std::sqrt(discriminant)) / (2.0f * a);
         if(temp < t_max && temp > t_min) {
             rec.t = temp;
             rec.p = r.point_at_parameter(rec.t);
             rec.normal = (rec.p - center(r.time)) / radius;
             rec.mat_ptr = mat_ptr;
             return true;
         }
     }

     return false;
 }

 bool moving_sphere::compute_bounding_box(float t0, float t1, aabb &box) const {
     aabb box0 = aabb(center(t0) - glm::vec3(radius), center(t0) + glm::vec3(radius));
     aabb box1 = aabb(center(t1) - glm::vec3(radius), center(t1) + glm::vec3(radius));

     box = surrounding_box(box0, box1);

     return true;
 }

#endif //RAYTRACER_MOVING_SPHERE_H
