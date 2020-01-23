#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

long long int solv(int n){
    long long int x = 1, y = 1;
    printf("%4d # ", n);
    long long int v = 1-n; // x*x - n*y*y
    for (;;){
        if (v == 1) {
            printf("%lld^2 - %lldx%lld^2 = 1\n", x, n, y);
            return x;
            break;
        }
        if (v<1){
            x++;
            v += (2*x-1);
        }
        else{
            y++;
            v -= (2*y-1)*n;
        }
        if (x>=20000000000){
            printf("N/A\n");
            return -1;
            break;
        }
    }
}
int main(){
    int na_cnt= 0 ;
    int max_x = 0;
    int pick = 0;
    int t = 2;
    for (int i = 2 ; i <= 300 ; ++i){
        int t_square = t*t;
        while (t_square < i){
            t++;
            t_square = t*t;
        }
        if (i == t_square){
            t++;
            continue;
        }
        int r = solv(i);
        if (r == -1) na_cnt++;
        if (r>max_x){
            max_x = r;
            pick = i;
            printf("Maximul X is %d at %d \n", max_x, pick);
        }
    }
    printf("N/A count : %d\n", na_cnt);
    printf("Maximul X is %d at %d \n", max_x, pick);
}

