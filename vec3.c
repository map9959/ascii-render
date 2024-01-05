#include "vec3.h"
double dot(vec3 v1, vec3 v2){
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
void normalize(vec3 *n){
    double norm = sqrt(dot(*n, *n));
    n->x /= norm;
    n->y /= norm;
    n->z /= norm;
}