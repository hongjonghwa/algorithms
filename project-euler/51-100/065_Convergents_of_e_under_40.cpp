#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int ea(int n){
    if (n==0) return 2;
    if (n%3 == 2) return 2*(n+1)/3;
    return 1;
}
/*
// root 2 for test
int ea(int n){
    if (n==0) return 1;
    return 2;
}
*/
long long int gcd(long long int p, long long int q){
    return q==0 ? p : gcd(q, p%q);
}
struct fraction{
    long long int n, d;
    fraction(long long int numerator, long long int denominator){
        n = numerator;
        d = denominator;
    }
    fraction add(fraction rhs){
        long long int nn = rhs.n*d + n*rhs.d;
        long long int dd = d*rhs.d;
        long long int g = gcd(nn,dd);
        return fraction (nn/g, dd/g);
    }
    fraction reverse(){
        return fraction(d,n);
    }
};
fraction calc(int n){
    /*
    1: a0 + 1/a1
    2: a0 + 1/(a1 + 1/a2)
    3: a0 + 1/(a1 + 1/(a2+1/a3))
    */
    fraction t(ea(n), 1);
    printf("n: %d   fraction : %lld/%lld\n", n, t.n, t.d);
    while (n--){
        t = t.reverse().add(fraction(ea(n),1) );
        printf(" n: %d   fraction : %lld/%lld\n", n, t.n, t.d);
    }
    
    return t;
}
int main(){
    fraction ret = calc(40);
    // fraction ret = calc(10);
}

