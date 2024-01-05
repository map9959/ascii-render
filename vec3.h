#include <math.h>
typedef struct vec3{
    double x;
    double y;
    double z;
} vec3;
void add(vec3 v1, vec3 v2);
double dot(vec3 v1, vec3 v2);
void normalize(vec3 *n);