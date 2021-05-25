#include<cstdio>
#include<cstring>
#include<math.h>
/*
https://codingcompetitions.withgoogle.com/codejam/round/00000000004330f6/00000000004329f4#analysis
https://conankuns.tistory.com/8
*/

void mat_mul(int a[2][2], int b[2][2], int ret[2][2]){
    int c[2][2] = {{0,0},{0,0}};
    for (int i = 0 ; i < 2; ++i)
        for (int j = 0 ; j < 2 ; ++j)
            for (int k = 0 ; k < 2 ; ++k)
                c[i][k] += a[i][j]*b[j][k] % 1000;
    for (int i = 0 ; i < 2; ++i)
        for (int j = 0 ; j < 2 ; ++j)
            ret[i][j] = c[i][j];
}

void exp(int n, int x[2][2], int ret[2][2] ){
    if (n == 1) ret[0][0]=x[0][0],ret[0][1]=x[0][1],ret[1][0]=x[1][0],ret[1][1]=x[1][1];
    else if (n%2 == 0){
        int r[2][2] = {{0,0},{0,0}};
        mat_mul(x,x,r);
        exp(n/2, r, ret);
    }else{
        int r[2][2] = {{0,0},{0,0}};
        exp(n-1, x, r);
        mat_mul (r, x, ret);
    }
}

int calc( int n){
    int u[2][2] = {{3,5},{1,3}};
    int u_n[2][2] = {{0,0},{0,0}};
    exp(n, u, u_n);

    int xn_mod = u_n[0][0] * 2 % 1000; 

    int ret= xn_mod -1;
    if (ret == -1) ret = 999;
    return ret;
}

int main(){
    int t, n; // 1 <= t <= 100 , 2 <= n <= 2000000000

    if (scanf("%d", &t)!=1) return 1;
    for (int i = 0 ; i < t ; ++i){
        if (scanf("%d", &n)!=1) return 1;
        printf("Case #%d: ", i+1);

        int ans = calc(n);
        printf("%03d\n", ans);
    }
}