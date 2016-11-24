/*!
 * \brief
 *
 * \author ddubois 
 * \date 13-Nov-16.
 */

#include <future>
#include <algorithm>
#include "bvh_node.h"

int box_x_compare(const hitable * a, const hitable * b) {
    if(a == NULL) {
        return false;
    } else if(b == NULL) {
        return true;
    }

    aabb box_left, box_right;
    if(!a->compute_bounding_box(0, 0, box_left) || !b->compute_bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box could be constructed";
    }

    return box_left.min.x - box_right.min.x < 0;
}

int box_y_compare(const hitable * a, const hitable * b) {
    if(a == NULL) {
        return false;
    } else if(b == NULL) {
        return true;
    }

    aabb box_left, box_right;
    if(!a->compute_bounding_box(0, 0, box_left) || !b->compute_bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box could be constructed";
    }

    return box_left.min.y - box_right.min.y < 0;
}

int box_z_compare(const hitable * a, const hitable * b) {
    if(a == NULL) {
        return false;
    } else if(b == NULL) {
        return true;
    }

    aabb box_left, box_right;
    if(!a->compute_bounding_box(0, 0, box_left) || !b->compute_bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box could be constructed";
    }

    return box_left.min.z - box_right.min.z < 0;
}

bvh_node::bvh_node(hitable ** l, int n, float time0, float time1) {
    int axis = int(3 * get_random_float());

    if(axis == 0) {
        std::sort(l, l + n, box_x_compare);

    } else if(axis == 1) {
        std::sort(l, l + n, box_y_compare);

    } else if(axis == 2) {
        std::sort(l, l + n, box_z_compare);
    }

    if(n == 1) {
        left = right = l[0];

    } else if(n == 2) {
        left = l[0];
        right = l[1];

    } else {
        left = new bvh_node(l, n / 2, time0, time1);
        right = new bvh_node(l + n/2, n - n/2, time0, time1);
    }

    aabb box_left, box_right;
    if(!left->compute_bounding_box(time0, time1, box_left) || !right->compute_bounding_box(time0, time1, box_right)) {
        std::cerr << "No bounding box could be computed";
    }

    box = surrounding_box(box_left, box_right);
}

bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    if(box.hit(r, t_min, t_max)) {
        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);

        if(hit_left && hit_right) {
            if(left_rec.t < right_rec.t) {
                rec = left_rec;
            } else {
                rec = right_rec;
            }
            return true;

        } else if(hit_left) {
            rec = left_rec;
            return true;

        } else if(hit_right) {
            rec = right_rec;
            return true;

        } else {
            return false;
        }

    } else {
        return false;
    }
}

bool bvh_node::compute_bounding_box(float t0, float t1, aabb &box) const {
    box = this->box;
    return true;
}

std::vector<glm::vec3> bvh_node::get_wireframe() {
    auto buffer = box.get_wireframe();
    auto left_buffer = left->get_wireframe();
    auto right_buffer = right->get_wireframe();

    buffer.insert(buffer.end(), left_buffer.begin(), left_buffer.end());
    buffer.insert(buffer.end(), right_buffer.begin(), right_buffer.end());

    return buffer;
}
