#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int r(int n){
    int ret = 0;
    while (n>0){
        ret *= 10;
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
bool check(int n){
    // if (n > 1e6) return false;
    // 2진 확인
    int hob = 21; // highest order bit
    for ( ; hob >= 0 ; hob--){
        if (n&(1<<hob)){
            break;
        }
    }
    int matchReq = (hob+1) / 2;
    for (int i = 0 ; i < matchReq ; ++i){
        int lbit = n&(1<<(hob-i))?1:0;
        int rbit = n&(1<<i)?1:0;
        if (lbit != rbit) return false;
    }

    printf("%d\t", n);
    for (int i = hob ; i >= 0 ; --i)
        printf("%d", n&(1<<i)?1:0);
    printf("\n");
    return true;
}
int main (){
    long long int sum = 0;
    for (int i = 1 ; i < 1000 ; ++i){
        int t = i, l = 0;
        while (t>0){
            l++;
            t/=10;
        }
        int r1 = i, r2 = i;
        r2 /= 10;
        for (int j = 0 ; j < l ; ++j){
            r1 *= 10;
            r2 *= 10;
        }
        int r3=r(i);
        r1 += r3;
        r2 += r3;
        if (check(r1)) sum += r1;
        if (check(r2)) sum += r2;
    }
    printf("sum is %lld\n", sum);
}

