#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int RESULT_D = 1, RESULT_N = 1;
int cancelling(int n, int x){
    // 10 < n < 100
    if ( n == x * 10 + x) return 0; // xx
    if ( n % 10 == x) return n / 10; // .x
    if ( n / 10 == x) return n % 10; // x.
    return n;
}
bool calc(int d, int n){
    for (int x = 1 ; x < 10 ; ++x){
        int dd = cancelling(d,x);
        int nn = cancelling(n,x);
        if (dd == 0 || nn == 0) continue;
        if (dd == d || nn == n) continue;
        if (dd * n == nn * d) return true;
    }
    return false;
}

int gcd(int p, int q){
    return p%q == 0 ? q : gcd(q, p%q);
}


int main (){
    for (int d = 10 ; d <= 99 ; ++d)
        for (int n = 10 ; n < d ; ++n)
            if (calc(d, n)){
                printf("%d/%d \n", n, d);
                RESULT_D *= d;
                RESULT_N *= n;
            }

    int d = gcd(RESULT_D, RESULT_N);
    printf("%d/%d -> %d/%d\n", RESULT_N, RESULT_D, RESULT_N/d, RESULT_D/d);
}

