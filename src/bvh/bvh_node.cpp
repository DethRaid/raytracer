//
// Created by David on 03-Apr-16.
//

#include <cstdlib>
#include <algorithm>
#include "bvh_node.h"
#include "../utils.h"

bool box_x_compare(const hitable * a, const hitable * b) {
    if(a == NULL) {
        return false;
    } else if(b == NULL) {
        return true;
    }
    aabb box_left, box_right;
    if(!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box in bvh_node constructor!";
    }

    return box_left.min().x() - box_right.min().x() < 0;
}

bool box_y_compare(const hitable * a, const hitable * b) {
    if(a == NULL) {
        return false;
    } else if(b == NULL) {
        return true;
    }
    aabb box_left, box_right;
    if(!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box in bvh_node constructor!";
    }

    return box_left.min().y() - box_right.min().y() < 0;
}

bool box_z_compare(const hitable * a, const hitable * b) {
    if(a == NULL) {
        return false;
    } else if(b == NULL) {
        return true;
    }
    aabb box_left, box_right;
    if(!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right)) {
        std::cerr << "No bounding box in bvh_node constructor!";
    }

    return box_left.min().z() - box_right.min().z() < 0;
}

bvh_node::bvh_node(std::vector<hitable *> list, float time0, float time1) {
    int axis = rand() % 3;
    if(axis == 0) {
        std::sort(list.begin(), list.end(), box_x_compare);
    } else if(axis == 1) {
        std::sort(list.begin(), list.end(), box_y_compare);
    } else {
        std::sort(list.begin(), list.end(), box_z_compare);
    }

    if(list.size() == 1) {
        left = right = list[0];
    } else if(list.size() == 2) {
        left = list[0];
        right = list[1];
    } else {
        int half_list_size = list.size() / 2;
        std::vector<hitable *> left_list(half_list_size);
        std::vector<hitable *> right_list(list.size() - half_list_size);

        for(int i = 0; i < list.size(); i++) {
            if(i < half_list_size) {
                left_list[i] = list[i];
            } else {
                right_list[i - half_list_size] = list[i];
            }
        }

        left = new bvh_node(left_list, time0, time1);
        right = new bvh_node(right_list, time0, time1);
    }

    aabb box_left, box_right;
    bool left_bb = left->bounding_box(time0, time1, box_left);
    bool right_bb = right->bounding_box(time0, time1, box_right);
    if(!left_bb || !right_bb) {
        std::cerr << "No bounding box in bvh constructor";
    }

    box = surrounding_box(box_left, box_right);
}

bool bvh_node::bounding_box(float t0, float t1, aabb &box) const {
    box = this->box;
    return true;
}

bool bvh_node::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
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
        }
    }
    return false;
}

