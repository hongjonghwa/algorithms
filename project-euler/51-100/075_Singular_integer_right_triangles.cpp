/* Prob 75 */

#include<stdio.h>
#include<assert.h>
typedef long long int lint;

int gcd(int p, int q){
    return q == 0 ? p : gcd(q, p%q);
}

lint sqrt(lint n){
    // prerequisite : n>=0
    lint lo = 0, hi = n+1;
    while (lo + 1 < hi){
        lint m = (lo+hi)/2;
        if (m*m > n) hi = m;
        else lo = m;
    }

    return lo;
}
int D[1500001];

/* 참조
 * https://projecteuler.net/overview=009
 */
void quadratic(){
    printf("### Quadratic method ###\n");
    int loop = 0;
    int L_MAX = 1500000;
    int M_LIMIT = 1000; // s: 2mn + 2m*m
    for (int m = 1 ; m <= M_LIMIT ; ++m){
        for (int n = 1 ; n < m ; ++n){
            int d = gcd(m,n);
            // Primitive Pythagorean Triplets
            if (d != 1) continue;
            /*
            if (m%2 == 0 && n%2 ==0) continue;
            if (m%2 == 1 && n%2 ==1) continue;
            */
            if ((m+n)%2 == 0) continue;

            int a = 2 * m * n;
            int b = m*m - n*n;
            int c = m*m + n*n;
            int s = a + b + c; // 2*m*(m+n) 으로 직접 계산하면 더 빠름
            if (s <= 150) printf("[%d] %lld, %lld, %lld  m,n: %d,%d\n", ++loop,a,b,c,m,n);
            if (s > L_MAX) break;

            int ss = s;
            while (ss <= L_MAX){
                D[ss]++;
                ss += s;
            }
        }
    }
    int ans = 0;
    for (int i = 1 ; i <= L_MAX ; ++i)
        if (D[i] == 1)
            ans++;
    printf("Answer is %d\n", ans);
}
void naive(){
    printf("### Naive method ###\n");
    int L_MAX = 1500000;
    L_MAX = 150;
    int L_LIMIT =  L_MAX / 3;
    int loop = 0;
    for (lint a = 1 ; a < L_LIMIT ; ++a){
        for (lint b = a ; b < L_LIMIT ; ++b){
            lint cc = a*a + b*b;
            lint c = sqrt(cc);
            lint s = a + b + c;
            if (s > L_MAX) break;
            if (c*c == cc){ // a,b,c is right triangle
                printf("[%d] %lld, %lld, %lld\n", ++loop,a,b,c);
            }
            // int c = a*a + b*b;
        }
    }
}
int main(){
    naive();
    quadratic();
}
