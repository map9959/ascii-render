#include <math.h>
typedef struct vec3{
    double x;
    double y;
    double z;
} vec3;
void vec_add(vec3 *v1, vec3 v2);
void vec_sub(vec3 *v1, vec3 v2);
void vec_mul(vec3 *v1, double s);
double dot(vec3 v1, vec3 v2);
void normalize(vec3 *n);