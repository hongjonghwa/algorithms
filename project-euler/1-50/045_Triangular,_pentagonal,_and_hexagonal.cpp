#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

long long int P[1000001];
long long int H[1000001];
void init(){
    for (long long int i = 1 ; i <= 1000000 ; ++i){
        P[i] = i * (3*i-1) / 2;
        H[i] = i * (2*i-1);
    }
}
bool is_pentagon_number(long long int n){
    int lo=0, hi=1000000;
    while (lo + 1 < hi){
        int mid = (lo+hi)/2;
        if (P[mid] < n) lo = mid;
        else hi = mid;
    }
    return P[hi] == n;
}
bool is_hexagonal_number(long long int n){
    int lo=0, hi=1000000;
    while (lo + 1 < hi){
        int mid = (lo+hi)/2;
        if (H[mid] < n) lo = mid;
        else hi = mid;
    }
    return H[hi] == n;
}

int main(){
    init();
    for (long long int i = 1 ; i < 1000000; ++i){
        long long int T = i*(i+1)/2;
        if (is_pentagon_number(T) && is_hexagonal_number(T))
            printf("%lld \n", T);
    }
}



