#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int D[10];
int DD[10];
int perm_times(int n){
    for (int i = 0 ; i < 10 ; ++i) D[i] = 0;
    int t = n;
    int limit = 1;
    while (t > 0){
        D[t%10]++;
        t /= 10;
        limit *= 10;
    }
    int times = 2;
    for (;; ++times){
        int ntimes = times * n ;
        if (ntimes >=  limit)break; 
        for (int i = 0 ; i<10 ; ++i) DD[i] = D[i];
        while (ntimes>0){
            DD[ntimes%10]--;
            ntimes /= 10;
        }
        bool fail = false;
        for (int i = 0 ; i < 10 ; ++i)
            if (DD[i]!=0){
                fail = true;
                break;
            }
        if (fail) break;
    }
    return times-1;

}
int main(){
    for (int i = 1 ; i< 1000000 ; ++i){
        int chk = perm_times(i);
        if (chk >= 2){
            printf("[%d] ", chk);
            for (int j = 1; j <= chk ; ++j)
                printf(" - %d", i*j);
            printf("\n");
        }
    }
}



