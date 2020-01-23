#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
int nCr(int n, int r){
    // 정의상 0! 은 1
    if (r == 0 || r == n) return 1;
    if (r > n/2) r = n - r; // r은 작은 수로 r <= 50

    long long int numerator = 1;
    long long int denominator = (1<<(r+1)) - 4;
    for (int i = n-r+1 ; i <= n ; ++i){
        numerator *= i;
        if (denominator){
            for (int j = 2 ; j <= r ; ++j){
                if (denominator & (1<<j))
                    if (numerator%j==0){
                        numerator/=j;
                        denominator &= ~(1<<j);
                    }
                        
            }
        }
        if (denominator >0 && numerator> 1e17){
            printf("something wrong %dC%d n: %lld, d: %lld\n", n, r, numerator, denominator);
            return -1;
        }
        if (denominator == 0 && numerator > 1e6)
            return 1000000;
    }
    if (denominator != 0 ){
        printf("why remaind deno %dC%d\n", n, r);
    }
    return numerator;

}
int cntMillion(int n){
    for (int r = 0; r < n/2; ++r){
        int v= nCr(n, r);
        if (v == -1){
            printf("Something wrong in %dC%d\n", n, r);
            return -1;
        }

        if (v >= 1000000){
            int cnt = n-r-r+1;
            // printf("%dC%d => count: %d\n", n, r, cnt);
            return cnt;
        }
    }
    return 0;
}
int NCR[101][101];
void memo(){
    NCR[0][0] = NCR[1][0] = NCR[1][1] = 1;
    for (int n = 2; n <= 100 ; ++n){
        NCR[n][0] = NCR[n][n] = 1;
        for (int r = 1 ; r <= n/2 ; ++r){
            int t = NCR[n][r-1] * (n-r+1) / r;
            NCR[n][n-r] = NCR[n][r] = t > 1000000 ? 1000000 : t;
        }
    }
}
int main(){
    // printf("TES %d\n", nCr(62,29));
    // printf("TES %d\n", nCr(62,30));
    int cnt;
    /* solv 1 */
    cnt = 0;
    for (int i = 1; i <= 100 ; ++i)
        cnt+=cntMillion(i);
    printf("Total counts: %d\n", cnt);
  
    /* solv 2 */
    cnt = 0;
    memo();
    for (int n = 1 ; n<=100 ; ++n)
        for (int r = 0 ; r <= n ; ++r){
            if (NCR[n][r]>=1000000) cnt++;
            //printf("%dC%d is %d\n", n, r , NCR[n][r]);
        }
    printf("Total counts: %d\n", cnt);
}



