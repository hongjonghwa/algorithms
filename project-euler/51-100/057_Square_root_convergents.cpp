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
template<class T>
inline void SWAP(T & a, T & b){
    T tmp = a;
    a = b;
    b = tmp;
}

int main(){
    unsigned long long int n = 1;
    unsigned long long int d = 1;
    int answer = 0;
    for (int i = 0 ; i < 1000; ++i){
        n += d; // step1 +1
        SWAP(n,d); // step2 swap
        n += d; // step3 +1 

        unsigned long long int nn = n;
        unsigned long long int dd = d;
        while(dd > 0){
            dd /= 10;
            nn /= 10;
        }
        if (nn) answer++;
        printf("%d: %llu/%llu %d =>  %.15lf\n", i+1, n, d, !!nn, double(n)/double(d));
        if (n > 1e16){
            n /= 10;
            d /= 10;
        }
    }

    printf("%d\n", answer);
}



