#include<stdio.h>
#include<assert.h>

typedef long long unsigned llu;

int T;
llu K;
int M;

llu gcd(llu a, llu b){
    return b == 0 ? a : gcd(b, a%b);
}

llu lcalc(llu n, int m){
    for (int i = 1; i < 1000000 ; ++i){
        if (gcd(n,i) == 1){
            m--;
            if (m == 0) return i;
        }
    }
    return -1;
}

llu solv(llu k, int m){
    for (int n = 1 ; n < 1000 ; ++n){
        printf("%d %lld %lld \n", n, lcalc(n,m), k^m);
        if (lcalc(n,m) == (k^n)) return n;
    }
    return -1;
}


int main(){
    if (scanf("%d", &T)!=1) return 1;
    for (int i = 0 ; i < T ; ++i){
        if (scanf("%lld%d", &K, &M)!=2) return 1;
        printf("#%d %lld\n", i+1, solv(K, M));
    }

}
