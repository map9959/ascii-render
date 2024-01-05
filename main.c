#include <stdio.h>
#include "vec3.h"

double rt_sphere(vec3 center, double r, vec3 origin, vec3 dir){
    vec3 Vp = {origin.x-center.x, origin.y-center.y, origin.z-center.z};
    double B = dot(Vp, dir);
    double C = dot(Vp, Vp)-r*r;
    double D = B*B-C;
    if(D > 0){
        return -B-sqrt(D);
    }
    return -1;
}
int main(int argc, char *argv[]){
    char grad[] = " .:-=+*#%@";

    int w = 64;
    int h = 32;
    char screen[h][w];

    vec3 sph = {0, 0, 0};
    vec3 Lloc = {1, 1, 1};
    vec3 Ldir = Lloc;
    normalize(&Ldir);
    double r = 0.7;

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            screen[i][j] = ' ';
            double normX = (j/(double)w)*2-1;
            double normY = (i/(double)h)*2-1;
            double fl = 3;
            vec3 V = {0, 0, fl};
            vec3 W = {normX, normY, -fl};
            normalize(&W);
            if(rt_sphere(sph, r, V, W) > 0){
                double t = rt_sphere(sph, r, V, W);
                vec3 S = {V.x+t*W.x, V.y+t*W.y, V.z+t*W.z};
                vec3 N = {S.x-sph.x, S.y-sph.y, S.z-sph.z};
                normalize(&N);

                double ambient = 0.1;

                vec3 l_dist_metric = {S.x-Lloc.x, S.y-Lloc.y, S.z-Lloc.z};
                double l_dist = dot(l_dist_metric, l_dist_metric);

                double diffuse = (dot(N, Ldir) > 0) ? dot(N, Ldir) * (1/l_dist) : 0;

                double t_light = diffuse + ambient;
                int light = (t_light > 1) ? 9 : (int)(t_light * 10);
                screen[i][j] = grad[light];
            }
        }
    }

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}