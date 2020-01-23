#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
// 10억 짜리 프라임 테이블
// 1e9 
// => bit vector 적용 /= 32 
// => 홀수만 /= 2
//
int bbt[15625001];
void bset(int n){
    int idx = n / 32;
    int mask = n % 32;
    bbt[idx] |= (1<<mask);
}
bool bget(int n){
    int idx = n / 32;
    int mask = n % 32;
    return bbt[idx] & (1<<mask);
}
void bclr(int n){
    // printf(" unset : %d \n", n);
    int idx = n / 32;
    int mask = n % 32;
    bbt[idx] &= ~(1<<mask);
}
bool isPrime(int n){
    if (n < 2) return false;
    if (n == 2) return true;
    if (n%2 == 0) return false;
    // printf("is prime %d %d\n", n, bget(n/2));
    return bget(n/2);
}
void e_big(){
    // all set
    for (int i = 0; i <= 15625000; ++i) bbt[i] = -1;
    for (int i = 3; i <= 31622 ; i += 2)
        if (isPrime(i))
            for (int j = i * i ; j <= 1e9; j += i*2)
                bclr(j/2);
}


void pandigital(int len, int idx, int v, int used){
    if (len == idx){
        if (isPrime(v)) printf("[%d] %d \n", len, v);
        return;
    }
    v*=10;
    for (int i = 1 ; i <= len ; ++i)
        if (!(used & (1<<i)))
            pandigital(len, idx+1, v+i, used | (1<<i));
}

int main(){
    e_big();
    /*
    int c = 0;
    for (int i = 1 ; i <= 100 ; ++i)
        if (isPrime(i))
            printf("%dth P: %d\n", ++c, i);
            */

    pandigital(2, 0, 0, 0);
    pandigital(3, 0, 0, 0);
    pandigital(4, 0, 0, 0);
    pandigital(5, 0, 0, 0);
    pandigital(6, 0, 0, 0);
    pandigital(7, 0, 0, 0);
    pandigital(8, 0, 0, 0);
    pandigital(9, 0, 0, 0);
    
}



