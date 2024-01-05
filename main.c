#include <stdio.h>
#include <time.h>
#include "vec3.h"

typedef struct sphere{
    vec3 center;
    double radius;
} sphere;

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

    sphere spheres[2];
    vec3 s0c = {0, 0, 0};
    spheres[0].center = s0c;
    spheres[0].radius = 0.55;
    vec3 s1c = {0.5, 0, 0.5};
    spheres[1].center = s1c;
    spheres[1].radius = 0.2;

    double theta = 0;
    double tilt = -2.1;
    while(theta < 12.5){
        vec3 Lloc = {sin(tilt)*cos(theta), sin(tilt)*cos(theta), sin(theta)};
        vec_mul(&Lloc, 1.1);

        vec3 s1c = {sin(tilt)*cos(theta*0.3)*0.6, cos(theta*0.3)*sin(tilt), sin(theta*0.3)*0.6};
        spheres[1].center = s1c;

        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                screen[i][j] = ' ';
                double normX = (j/(double)w)*2-1;
                double normY = (i/(double)h)*2-1;
                double fl = 1.2;
                vec3 V = {0, 0, fl};
                vec3 W = {normX, normY, -fl};
                normalize(&W);

                double min_t = 10000;
                for(int s = 0; s < 2; s++){
                    vec3 sph = spheres[s].center;
                    double r = spheres[s].radius;
                    double t = rt_sphere(sph, r, V, W);
                    if(t > 0 && t < min_t){
                        min_t = t;
                        vec3 S = {V.x+t*W.x, V.y+t*W.y, V.z+t*W.z};

                        double ambient = 0.1;
                        double t_light = ambient;

                        vec3 l_dist_metric = {Lloc.x-S.x, Lloc.y-S.y, Lloc.z-S.z};
                        //double l_dist = dot(l_dist_metric, l_dist_metric);
                        double l_dist = 3;
                        vec3 Ldir = l_dist_metric;
                        normalize(&Ldir);

                        double shadow_t = -1;
                        vec3 S_prime = {S.x+0.001*Ldir.x, S.y+0.001*Ldir.y, S.z+0.001*Ldir.z};
                        for(int s2 = 0; s2 < 2; s2++){
                            shadow_t = rt_sphere(spheres[s2].center, spheres[s2].radius, S_prime, Ldir);
                            if(shadow_t >= 0){
                                break;
                            }
                        }
                        if(shadow_t < 0){
                            vec3 N = {S.x-sph.x, S.y-sph.y, S.z-sph.z};
                            normalize(&N);
                            double diffuse = (dot(N, Ldir) > 0) ? dot(N, Ldir) * (1/l_dist) : 0;

                            vec3 Rm = N;
                            vec_mul(&Rm, 2*dot(Rm, Ldir));
                            vec_sub(&Rm, Ldir);
                            double shine = 300;
                            double specular = pow(-dot(Rm, W), shine);
                            specular = (specular > 0) ? specular : 0;

                            t_light += diffuse + diffuse * specular;
                        }

                        int light = (t_light > 1) ? 9 : (int)(t_light * 10);
                        screen[i][j] = grad[light];
                    }
                }
            }
        }

        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                printf("%c", screen[i][j]);
            }
            printf("\n");
        }

        int ms = 40000;
        clock_t start_time = clock();
        while(clock() < start_time + ms);

        printf("\e[1;1H\e[2J");

        theta += 0.1;
    }
}