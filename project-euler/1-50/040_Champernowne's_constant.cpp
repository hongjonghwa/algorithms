#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))


int exp(int n){
    // n > 0
    // if (n == 0) return 0;
    int ret = 1;
    while (n--){
        ret *= 10;
    }
    return ret;
}
void pick(int d, int digit, int n){
    printf("%d %d %d\n", d, digit, n);
}
int main (){
    int d = 1;
    for (int digit = 1 ; digit < 7; ++digit){
        int s = exp(digit-1), e = exp(digit);
        for (int i = s ; i < e ; ++i){
            int next_d = d + digit;
            if(1 >= d && 1 < next_d) pick (d, digit, i);
            if(10 >= d && 10 < next_d) pick (d, digit, i);
            if(100 >= d && 100 < next_d) pick (d, digit, i);
            if(1000 >= d && 1000 < next_d) pick (d, digit, i);
            if(10000 >= d && 10000 < next_d) pick (d, digit, i);
            if(100000 >= d && 100000 < next_d) pick (d, digit, i);
            if(1000000 >= d && 1000000 < next_d) pick (d, digit, i);
            d = next_d;
        }
    }

}

