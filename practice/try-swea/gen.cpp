#include<stdio.h>

int main(){
    freopen("gen.txt", "wt", stdout);
    printf("%d\n", 1);
    int N = 100000;
    printf("%d\n", N);
    for (int i = 1 ; i <= 2*N-1 ; ++i)
        printf("%d \n", i);
}

