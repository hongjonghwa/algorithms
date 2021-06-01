/*
  Manhattan 거리일 때는  medium 노드 포지션.
  Squred Euclide 거리일 때는 mean 포지션.

  하지만 문제는 Euclide 거리
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

#define N 10
#define ABS(x) ((x)<0?-(x):(x))

double X[N][3];

double rr(){
    return rand()%9 + 1; // int 1 ~ 9
}

double dist(double a, double b){
    double ret = ABS(a-b);
    return ret; // manhattan
    // return ret*ret; // euclide
    // return ret*ret*ret; // l3
}

double distance(double a[3], double b[3]){
    double s = 0;
    for (int j = 0 ; j < 3 ; ++j)
        s+= dist(a[j], b[j]);
    //return sqrt(s);
    return s;
}

int main(){
    srand(42);
    for (int i = 0 ; i < N ; ++i)
        for (int j = 0 ; j < 3 ; ++j)
            X[i][j] = rr();

    for (int j = 0 ; j < 3 ; ++j){
        double s = 0;
        for (int i = 0 ; i < N ; ++i) {
            printf( "%.2f ", X[i][j]);
            s += X[i][j];
        }
        printf( "\n mean [%d] is %f\n", j, s/N);
    }

    double ST = 0, ED = 10, INC = 0.02;
    double min_sum_dist = 1e20;
    double save[3] = {0,0,0};
    for (double x = ST ; x <= ED ; x += INC)
        for (double y = ST ; y <= ED ; y += INC)
            for (double z = ST ; z <= ED ; z += INC){
                double b[3] = {x,y,z};
                double s = 0;
                for (int i = 0 ; i < N ; ++i)
                    s += distance(X[i], b);
                if (s < min_sum_dist){
                    min_sum_dist = s;
                    save[0] = x, save[1] = y, save[2] = z;
                }
            }
    printf("best is (%f, %f, %f)\n", save[0], save[1], save[2]);
}