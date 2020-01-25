#include<stdio.h>
#include<assert.h>

int D[4000000]; // factorial sum in digits
int fact_sum_in_digits(int d){
    if (D[d] != 0) return D[d];
    // 전처리를 하면 조금 더 빨라질 것
    int n = d;
    int ret = 0;
    while(n>0){
        ret += D[n % 10];
        n /= 10;
    }
    return D[d] = ret;
}
int LOOP[100];
int LIDX;
int chain_length(int n){
    LIDX = 0;
    LOOP[LIDX++] = n;
    for (;LIDX<100;){ // safe guard
        n = fact_sum_in_digits(n); // next 
        for (int j = 0 ; j < LIDX; ++j) // not in loop
            if (n == LOOP[j]) 
                return LIDX;
        LOOP[LIDX++] = n;
    }
    assert(0);
    return 99999;
}
int main() {
    D[0] = 1;
    for (int i = 1 ; i < 10 ; ++i)
        D[i]  = D[i-1] * i;

    int ans = 0;
    for (int i = 1 ; i <= 1000000 ; ++i){
        int l = chain_length(i);
   
        if (l >= 60) {

            ans++;
            if (l > 60) printf("chain of %d is %d \n", i, l);
        }
    }
    printf("Answer is %d\n", ans);
}
