#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int P5[10];

int main (){
    for (int i = 0 ; i < 10 ; ++i)
        P5[i] = i * i * i * i * i;

    int ret = 0;
    for (int i = 2 ; i < 100000000 ; ++i){
        int t = i;
        int s = 0;
        while(t>0){
            s += P5[t%10];
            t /= 10;
        }
        // printf(" %d  %d \n", i, s);
        if (s == i){
            printf(" => %d \n", i);
            ret += i;
        }
    }
    printf("Answer is %d\n", ret);
    
}
