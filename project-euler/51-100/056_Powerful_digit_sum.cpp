#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<limits.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int digit_sum(long long int n){
    int ret = 0;
    while (n>0){
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

int main(){
    int answer = 0;
    long long int M = 1e10;
    long long int D[20];
    for (int a = 2 ; a < 100 ; ++a){
        D[0] = 1;
        for (int i = 1 ; i < 20 ; ++i) D[i] = 0;

        unsigned long long int debug_sum = 1;
        for (int b = 1; b < 100 ; ++b){
            // j를 곱함
            for (int i = 0 ; i < 20 ; ++i) 
                D[i] *= a;
            for (int i = 0 ; i < 19 ; ++i)
                if (D[i]>=M){
                    D[i+1] += (D[i]/M);
                    D[i] %= M;
                }
            /*
            for (int i = 0 ; i < 20 ; ++i) 
                printf("-%lld", D[i]);
            printf("\n");
            */

            int dsum = 0;
            for (int i = 0 ; i < 20 ; ++i){
                dsum += digit_sum(D[i]);
                // printf(" D:%lld F:%d S:%d\n", D[i], digit_sum(D[i]), dsum);
            }

            debug_sum*=a;
            printf("[Debug] %d^%d %llu %d ", a, b, debug_sum, digit_sum(debug_sum) );
            printf("[Real]  %llu  \n", dsum );
            if (dsum > answer) answer = dsum;
        }
    }
    printf("Answer is %d\n", answer);
}



