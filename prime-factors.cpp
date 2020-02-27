#include<stdio.h>


void factors(int n){
    for (int i = 2 ; i*i <=n ; ++i){
        while (n%i == 0){
            printf(" %d\n", i);
            n /= i;
        }
    }
    if (n > 1) printf(" %d\n", n);
}
int main(){
    int n;
    while (1){
        if (scanf("%d", &n) != 1) return -1;
        factors(n);
    }
}
