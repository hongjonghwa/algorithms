#include<stdio.h>
#include<assert.h>
#define MIN(a,b) ((a)<(b) ? (a) : (b))

int D[101][100];
int bt(int n, int m){
    // printf("n,m %d,%d\n", n,m);
    if (n==0) return 1;
    if (D[n][m]>0) return D[n][m];
    int ans = 0;
    for (int i = MIN(m,n) ; i > 0 ; --i)
        ans += bt(n-i, i);
    return D[n][m] = ans;
}
int solv(int n){
    return bt(n, n-1);
}
int main(){
    printf("Test 5 is %d\n", solv(5));
    printf("Answer is %d\n", solv(100));
}
