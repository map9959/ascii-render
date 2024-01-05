#include "vec3.h"
void vec_add(vec3 *v1, vec3 v2){
    v1->x += v2.x;
    v1->y += v2.y;
    v1->z += v2.z;
}
void vec_sub(vec3 *v1, vec3 v2){
    v1->x -= v2.x;
    v1->y -= v2.y;
    v1->z -= v2.z;
}
void vec_mul(vec3 *v1, double s){
    v1->x *= s;
    v1->y *= s;
    v1->z *= s;
}
double dot(vec3 v1, vec3 v2){
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
void normalize(vec3 *n){
    double norm = sqrt(dot(*n, *n));
    n->x /= norm;
    n->y /= norm;
    n->z /= norm;
}