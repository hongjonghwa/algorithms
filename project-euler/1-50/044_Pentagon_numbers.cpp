#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int P[10001];
void init(){
    for (int i = 1 ; i <= 10000 ; ++i)
        P[i] = i * (3*i-1) / 2;
}
bool is_pentagon_number(int n){
    int lo=0, hi=10000;
    while (lo + 1 < hi){
        int mid = (lo+hi)/2;
        if (P[mid] < n) lo = mid;
        else hi = mid;
    }
    return P[hi] == n;
}
bool check(int i, int j){
    int s = P[i]+P[j];
    if (!is_pentagon_number(s)) return false;
    int d = P[i]-P[j];
    d = ABS(d);
    return is_pentagon_number(d);
}

int main(){
    init();
    for (int i = 1 ; i < 10000; ++i)
        for (int j = i+1 ; j <= 10000 ; ++j)
            if (check(i,j)){
                printf("%d-%d Pk %d Pj %d, sum %d, diff %d\n",i,j,P[i],P[j], P[i]+P[j], ABS(P[i]-P[j]));
            }
                
    for (int i = 0 ; i <=10 ; ++i)
        printf("%d\n", P[i]);
        printf("%d\n", P[9000]);
        printf("%d\n", P[8000]);
        printf("%d\n", P[7000]);
        printf("%d\n", P[10000]);
}



