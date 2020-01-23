#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int F[10];

int calc(int n){
    int ret = 0;
    while (n>0){
        ret += F[n%10];
        n /= 10;
    }
    return ret;
}

int main (){
    F[0] = F[1] = 1; // 주의: 0! 는 1이다 
    for (int i = 2; i < 10 ; ++i) F[i] = F[i-1] * i;
    // for (int i = 1; i < 10 ; ++i) printf("%d %d \n", i, F[i]);
 
    long long int ret = 0;
    for (int i = 3 ; i < 1e9 ; ++i){
        // printf("D: %d %d \n", i, calc(i));
        if (i == calc(i)){
            printf("%d \n");
            ret += i;
        }
    }
    printf("SUM: %lld \n", ret);
}

