#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int X[1001][1001];
inline void set(int y, int x, int v){
    X[y+500][x+500] = v;
}
inline int get(int y, int x){
    return X[y+500][x+500];
}
int main (){
    int DX[4] = {1,0,-1,0};
    int DY[4] = {0,1,0,-1};
    int D = 0;
    int y = 0, x = 0;
    int v = 0;
    bool breakAll = false;
    for (int i = 1; ; ++i){ // i < v <= 25){
        for (int j = 0 ; j < 2; ++j){
            for (int k = 0; k < i ; ++k){ // i < v <= 25){
                set(y,x,++v);
                if (v == 1001*1001){
                    breakAll = true;
                    break;
                }
                y+=DY[D];
                x+=DX[D];
            }
            D = (D + 1) % 4;
            if (breakAll) break;
        }
        if (breakAll) break;
    }

    // debug
    /*
    for (int y = -5 ; y <= 5 ; ++y){
        for (int x = -5 ; x <= 5 ; ++x)
            printf("%d\t", get(y,x));
        printf("\n");
    }
    */

    long long int ret = -get(0,0);
    for (int i = -500 ; i <= 500 ; ++i) ret += get(i, i);
    for (int i = -500 ; i <= 500 ; ++i) ret += get(i, -i);
    printf("result is %lld.\n", ret);
}
