#include <math.h>
#include "vector.h"

// Implementations of Vector 2D functions
float vec2_length(Vec2f v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vec2f vec2_add(Vec2f a, Vec2f b) {
    Vec2f result = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
    return result;
}

Vec2f vec2_sub(Vec2f a, Vec2f b) {
    Vec2f result = {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
    return result;
}

Vec2f vec2_mul(Vec2f v, float factor) {
    Vec2f result = {
        .x = v.x * factor,
        .y = v.y * factor
    };
    return result;
}

Vec2f vec2_div(Vec2f v, float factor) {
    Vec2f result = {
        .x = v.x / factor,
        .y = v.y / factor
    };
    return result;
}

float vec2_dot(Vec2f a, Vec2f b) {
    return (a.x * b.x) + (a.y * b.y);
}
void vec2_normalize(Vec2f* v) {
    float length = sqrt(v->x * v->x + v->y * v->y);
    v->x /= length;
    v->y /= length;
}

// Implementations of Vector 3D functions
float vec3_length(Vec3f v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3f vec3_add(Vec3f a, Vec3f b) {
    Vec3f result = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
    return result;
}

Vec3f vec3_sub(Vec3f a, Vec3f b) {
    Vec3f result = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
    return result;
}

Vec3f vec3_mul(Vec3f v, float factor) {
    Vec3f result = {
        .x = v.x * factor,
        .y = v.y * factor,
        .z = v.z * factor
    };
    return result;
}

Vec3f vec3_div(Vec3f v, float factor) {
    Vec3f result = {
        .x = v.x / factor,
        .y = v.y / factor,
        .z = v.z / factor
    };
    return result;
}

Vec3f vec3_cross(Vec3f a, Vec3f b) {
    Vec3f result = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x
    };
    return result;
}

float vec3_dot(Vec3f a, Vec3f b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3f vec3_rotate_x(Vec3f v, float angle) {
    Vec3f rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

Vec3f vec3_rotate_y(Vec3f v, float angle) {
    Vec3f rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

Vec3f vec3_rotate_z(Vec3f v, float angle) {
    Vec3f rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };
    return rotated_vector;
}

void vec3_normalize(Vec3f* v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

// Vector conversion functions
Vec4f vec4_from_vec3(Vec3f v){
    Vec4f result = {v.x, v.y, v.z, 1.0};
    return result;
}
Vec3f vec3_from_vec4(Vec4f v){
    Vec3f result = {v.x, v.y, v.z};
    return result;
}

Vec2f vec2_from_vec4(Vec4f v) {
    Vec2f result = {v.x, v.y};
    return result;
}

Vec3f vec3_new(float x, float y, float z) {
    Vec3f result = { x, y, z };
    return result;
}

Vec3f vec3_clone(Vec3f* v) {
    Vec3f result = { v->x, v->y, v->z };
    return result;
}