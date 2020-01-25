#include<stdio.h>
#include<assert.h>
#define MIN(a,b) ((a)<(b) ? (a) : (b))

bool isPrime[5001];
void e(){
    for (int i = 2; i <= 5000; ++i) isPrime[i] = 1;
    for (int i = 2; i <= 100 ; ++i)
        if (isPrime[i])
            for (int j = i*i ; j <= 5000 ; j += i)
                isPrime[j] = 0;
}

long long int D[5001][5001];
long long int bt(int n, int m){
    // printf("n,m %d,%d\n", n,m);
    if (D[n][m] != -1) return D[n][m];
    if (n==0) return 1;
    // if (n<0) return 0; // 필요? 
    long long int ans = 0;
    for (int i = MIN(m,n) ; i > 1 ; --i)
        if (isPrime[i]) 
            ans += bt(n-i, i);
    return D[n][m] = ans;
}
int solv(int n){
    return bt(n, n-1);
}
int main(){
    for (int i = 0 ; i <= 5000; ++i)
        for (int j= 0 ; j <= 5000 ; ++j)
            D[i][j] = -1;
    e();
    /*
    // 확인
    int c = 0;
    for (int i = 1 ; i<= 100 ; ++i)
        if (isPrime[i])
            printf("%d %d\n", ++c, i);
    */
    printf("Test 10 is %d\n", solv(10));
    // printf("Test 5000 is %lld\n", solv(5000));
    for (int i = 1; i < 100  ;  ++i){
        int s = solv(i);
        printf("%d => %d\n", i, s);
        if (s >=  5000) break;
    }

}
