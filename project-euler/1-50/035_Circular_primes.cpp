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

bool is_circular_prime(int n){

    int t = n;
    int len = 0;
    while (t > 0){
        t /= 10;
        len++;
    }
    int o = 1;
    for (int i = 0 ; i < len - 1 ; ++i) o *= 10;
    // printf("%d len : %d o: %d \n", n, len, o);

    for (int i = 0 ; i < len -1 ; ++i){
        n = (n%o) * 10 + (n/o);
        if (!isPrime[n]) return false;
        // printf("--> %d \n", n);
    }
    return true;
}

int main (){
    e();
    int cnt = 0;
    for (int i = 2 ; i <= 1000000 ; ++i)
        if (isPrime[i] && is_circular_prime(i))
            printf("%dth circular : %d\n", ++cnt, i);
}

