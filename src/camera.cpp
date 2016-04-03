//
// Created by David on 03-Apr-16.
//

#include "camera.h"
#include "utils.h"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float fov, float aspect, float aperture, float focus_dist) {
    lens_radius = aperture / 2;

    float theta = (float) (fov * PI / 180);
    float half_height = (float) tan(theta / 2);
    float half_width = aspect * half_height;

    vec3 w = unit_vector(lookfrom - lookat);
    vec3 u = unit_vector(cross(vup, w));
    vec3 v = cross(w, u);

    origin = lookfrom;
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * focus_dist * half_width * u;
    vertical = 2 * focus_dist * half_height * v;
}

ray camera::get_ray(float u, float v) {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray(origin + offset, lower_left_corner + u * horizontal + v * vertical - origin - offset);
}




