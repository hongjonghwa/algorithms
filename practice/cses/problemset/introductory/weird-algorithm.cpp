#include<stdio.h>

int main(){
    unsigned long long int n;
    if (scanf("%llu", &n) != 1) return -1;
    printf("%llu", n);
    while(n != 1){
        if (n & 1) n = 3*n+1;
        else n /= 2;
        printf(" %llu", n);
    }
}
