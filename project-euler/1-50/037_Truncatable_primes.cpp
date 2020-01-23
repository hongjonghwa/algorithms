#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

bool isPrime[1000001];
void e(){
    for (int i = 2 ; i <= 1000000 ; ++i) isPrime[i] = true;
    for (int i = 2 ; i <= 1000 ; ++i)
        if (isPrime[i])
            for (int j = i * i ; j <= 1000000 ; j += i)
                isPrime[j] = false;
}
bool check(int n){
    if (n < 10) return false;
    if (!isPrime[n]) return false;
    int t = n;
    int l = 0;
    int e = 1;
    while (t > 0){
        // printf(" chk : %d \n", t);
        if (!isPrime[t]) return false;
        l++;
        t /= 10;
        e *= 10;
    }
    t = n;
    e /= 10;
    t %= e;
    e /= 10;
    while (e > 0){
        // printf(" chk : %d \n", t);
        if (!isPrime[t]) return false;
        t %= e;
        e /= 10;
    }
    printf("%d \n", n);
    return true;

}
int main (){
    e();
    long long int ret = 0;
    for (int i = 11 ; i <= 1000000 ; i += 2)
        if (check(i))
            ret += i;
    printf(" sum : %lld\n", ret);
    return 0;
}

