#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<limits.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

#define NN 900000000
#define SN     30000

int X[NN/32 + 1];
void all_set(){
    for (int i = 0 ; i < NN/32+1 ; ++i)
        X[i] = -1;
}
void clr(int n){
    int mask = n & 31; // 0 ~ 31;
    int idx = n >> 5;
    X[idx] &= ~(1 << mask);
}
bool get(int n){
    int mask = n & 31; // 0 ~ 31;
    int idx = n >> 5;
    return X[idx] & (1 << mask);
}
void e(){
    // for (int i = 2; i <= NN; ++i) isPrime[i] = true;
    all_set();
    clr(0);
    clr(1);
    for (int i = 2; i <= SN; ++i)
        if (get(i))
            for (int j = i*i; j <= NN; j+=i)
                clr(j);
}

bool is_prime(int n){
    return get(n);
}

int main(){
    e();
    int N = 0;
    int D = 1;
    int c = 1;
    for (int i = 1; ; ++i){
        int step = i * 2;
        for (int j = 0 ; j < 4 ; ++j){
            c+=step;
            if (c>NN) return -1;
            if (is_prime(c)) N++;
        }
        D+=4;
        printf( "len: %d(%d) N: %d D: %d, RATIO: %f\n", i*2+1, c,N, D, double(N)/D);
        if (N*10 < D) break;
    }
}



