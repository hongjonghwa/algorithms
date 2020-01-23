#include<stdio.h>

int D = 8;

int gcd(int p, int q){
    return q == 0 ? p : gcd(q, p%q);
}

int main(){
    long long int maxn = 0, maxd = 1;
    for (int d = 3 ; d <= 1000000 ; ++d){
        /* method1
        int n = d * 3 / 7;
        if (d%7 == 0) n--;
        */
        // method2
        int n = (d * 3 - 1) /7;
        /*
        while (gcd(n,d) != 1){ n--; } // 불필요 - 만약 기약분수가 아니여도, 이전에 이미 약분한 분수를 셌을 것!
        */
        if (n*maxd > d*maxn){
            printf("%d/%d = %.17f\n", n, d, double(n)/d);
            maxn = n;
            maxd = d;
        }
    }

}
