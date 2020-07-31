#include<stdio.h>

long long int MOD5 = 1e5;
long long int MOD10 = 1e10;

long long int product(long long int p, long long int q){
    if (p < 1e9 || q < 1e9) return p * q % MOD10;
    p %= MOD10;
    q %= MOD10;
    long long int p_lo = p % MOD5;
    long long int p_hi = p - p_lo;
    long long int q_lo = q % MOD5;
    long long int q_hi = q - q_lo;
    return (p_lo*q_lo + p_lo*q_hi + p_hi*q_lo) % MOD10;
}

long long int pow(long long int p, int q){
    if (q == 0) return 1;
    if (q & 1) return product(pow(p, q-1), p) % MOD10;
    return pow(product(p,p), q/2) % MOD10;
}

int main(){
    long long int ret = (28433ll * pow(2, 7830457) + 1) % MOD10;
    printf("%I64d\n", ret);
}
