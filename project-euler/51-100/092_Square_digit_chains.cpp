// ! 92
#include<stdio.h>
#define N 10000000

char X[N]; // arrives at  

int digits_square(int x){
    int ret = 0;
    while (x){
        int t = x%10;
        ret += t*t;
        x /= 10;
    }
    return ret;
}
int bt(int n){
    if (X[n]) return X[n];
    return X[n] = bt(digits_square(n));
}
int main(){
    X[1] = 1;
    int n = 89;
    while (!X[n]){
        printf("%d ",n);
        X[n] = 89;
        n = digits_square(n);
    }
    printf("\n");

    int answer = 0;
    for (int i = 1 ; i < N ; ++i){
        int r = bt(i);
        if (r == 89) answer++;
    }
    printf("Answer is %d\n", answer);

}
