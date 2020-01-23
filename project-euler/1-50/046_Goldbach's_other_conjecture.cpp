#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

bool isPrime[1000001];
void e(){
    isPrime[2] = true;
    for (int i = 3 ; i <= 1000000 ; i+=2) isPrime[i] = true;
    for (int i = 3 ; i <= 1000 ; i+=2)
        if (isPrime[i])
            for (int j = i * i ; j <= 1000000 ; j+=(i*2))
                isPrime[j] = false;
}

int integer_sqrt(int n){
    int lo = 0, hi = n;
    while(lo+1<hi){
        int mid = (lo+hi)/2;
        if (mid*mid < n) lo = mid;
        else hi = mid;
    }
    if (hi*hi == n) return hi;
    return -1;
}
bool check(int n){
    // n is odd
    for (int i = 3 ; i < n ; i+=2){
        if (isPrime[i]){
            int t = n - i; // even
            t /= 2;
            int sq = integer_sqrt(t);
            if (sq>0){
                printf("%d = %d + 2 * %d^2(%d)\n", n, i, sq, sq*sq);
                return true;
            }
        }
    }
    return false;
}

int main(){
    e();
    // int c = 0;
    for (int i = 3 ; i <= 10000 ; i+=2) 
        if (!isPrime[i] && !check(i)){ // composite number
            printf("%d is impossible !!!\n", i);
            break;
        } 
}



