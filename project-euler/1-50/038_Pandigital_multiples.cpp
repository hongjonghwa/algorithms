#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

bool check(int n){
    int used = 0 ;
    for (int i = 1 ; used != 1022 ; ++i){
        int t = n * i ;
        while (t > 0){
            int digit = t % 10;
            if (digit == 0) return false;
            if (used & (1<<digit)) return false;
            used += (1<<digit);
            t /= 10;
        }
    }
    return true;
}
void report(int n){
    int used = 0 ;
    for (int i = 1 ; used != 1022 ; ++i){
        int t = n * i ;
        printf("%d ", t);
        while (t > 0){
            int digit = t % 10;
            used += (1<<digit);
            t /= 10;
        }
    }
    printf("\n");
}
int main (){
    for (int i = 1 ; i < 10000 ; ++i)
        if (check(i))
            report(i);
}

