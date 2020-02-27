#include<stdio.h>
#define N 1000

bool isPrime[N+1];
void e(){
    for (int i = 2 ; i <= N ; ++i) isPrime[i] = 1;
    for (int i = 2 ; i*i <= N ; ++i)
        if (isPrime[i])
            for (int j = i * i ; j <= N ; j += i)
                isPrime[j] = 0;
}
int main(){
    e();
    for (int i = 1, c = 0 ; i <= 100 ; ++i)
        if (isPrime[i])
            printf("[%d] %d\n", ++c, i);
}
