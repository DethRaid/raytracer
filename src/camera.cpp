//
// Created by David on 03-Apr-16.
//

#include "camera.h"
#include "utils.h"

camera::camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float fov, float aspect, float aperture, float focus_dist) {
    lens_radius = aperture / 2;

    float theta = (float) (fov * PI / 180);
    float half_height = (float) tan(theta / 2);
    float half_width = aspect * half_height;

    glm::vec3 w = glm::normalize(lookfrom - lookat);
    glm::vec3 u = glm::normalize(cross(vup, w));
    glm::vec3 v = cross(w, u);

    origin = lookfrom;
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * focus_dist * half_width * u;
    vertical = 2 * focus_dist * half_height * v;
}

ray camera::get_ray(float u, float v) {
    glm::vec3 rd = lens_radius * random_in_unit_disk();
    glm::vec3 offset = glm::vec3(u * rd.x, v * rd.y, 0);
    return ray(origin + offset, lower_left_corner + u * horizontal + v * vertical - origin - offset);
}




