#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int main(){
    int cnt = 0;
    for (int i = 1 ; i < 10 ; ++i){
        long long int t = 1;
        int digits=1;
        long long int exp = 10;
        int omit = 0;
        for (int j = 1 ; j<=25 ; ++j){
            t *= i;
            if (t > exp){
                digits++;
                exp *= 10;
            }
            if (t >= 1e16){
                omit++;
                t /= 10;
                exp /= 10;
            }
            if (digits<j) break;
            /* overflow 방지 */
            if (digits == j)
                printf("[%3d] %d^%d = %lld e%d (%d)\n", ++cnt, i,j,t,omit,digits);

        }
    }
}

