/*!
 * \brief
 *
 * \author ddubois 
 * \date 24-Nov-16.
 */

#include <math.h>
#include <random>
#include "camera.h"
#include "utils.h"

camera::camera(unsigned samples,
               glm::ivec2 viewport, glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup,
               float vfov, float aspect, float aperture, float focus_dist,
               float t0, float t1)
        : samples(samples), viewport(viewport), time0(t0), time1(t1), origin(lookfrom), look_target(lookat), up(up) {
    lens_radius = aperture / 2.0f;

    float theta = vfov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0f);
    float half_width = aspect * half_height;

    origin = lookfrom;
    w = glm::normalize(lookfrom - lookat);
    u = glm::normalize(glm::cross(vup, w));
    v = glm::cross(w, u);

    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2.0f * half_width * focus_dist * u;
    vertical = 2.0f * half_height * focus_dist * v;
}

ray camera::get_ray(float s, float t) {
    static thread_local std::random_device random;
    glm::vec3 rd = lens_radius * random_in_unit_disk();
    glm::vec3 offset = u * rd.x + v * rd.y;
    float time = time0 + random() * (time1 - time0);
    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
}

glm::vec3 camera::get_position() {
    return origin;
}

glm::vec3 camera::get_look_target() {
    return look_target;
}

glm::vec3 camera::get_up() {
    return up;
};

