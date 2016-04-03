//
// Created by David on 02-Apr-16.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H


#include <cmath>
#include <iostream>

class vec3 {
public:
    vec3() {};
    vec3(float e0) {e[0] = e0; e[1] = e0; e[2] = e0;}
    vec3(float e0, float e1, float e2) {e[0] = e0; e[1] = e1; e[2] = e2;}

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const {return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float length() const { return (float) sqrt(squared_length()); }
    inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void normalize();

    float e[3];
};

inline vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();

    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();

    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();

    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();

    return *this;
}

inline vec3& vec3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

inline vec3& vec3::operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;

    return *this;
}

inline std::istream & operator>>(std::istream &is, vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream & operator<<(std::ostream &os, vec3 &t) {
    os << t.x() << " " << t.y() << " " << t.z();
    return os;
}

inline void vec3::normalize() {
    float k = (float) (1.0 / length());
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return v1 + -v2;
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator/(const vec3 &v, float t) {
    return (1.0 / t) * v;
}

inline vec3 operator*(const vec3 &v, float t) {
    return t * v;
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(),
                -(v1.x() * v2.z() - v1.z() * v2.x()),
                v1.x() * v2.y() - v1.y() * v2.x());
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif //RAYTRACER_VEC3_H
