#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
int sq_floor(int n){
    int lo = 0 , hi = n;
    while (lo+1<hi){
        int mid = (lo+hi)/2;
        // printf("%d %d %d\n", lo, hi, mid);
        if (mid*mid <= n) lo = mid;
        else hi = mid;
    }
    return lo;
}
int CYCLE[10000][100];
void init_cycle(){
    for (int i = 0 ; i < 10000 ; ++i)
        for (int j = 0 ; j < 100 ; ++j)
            CYCLE[i][j] = 0;
}
int report_period(int n, int minus, int denominator, int idx){
    /* 
     * (Root(n)-minus) / denominator 형태
     */
    if (idx == n+1) {
        printf("Something wrong : %d %d %d %d\n", n, minus, denominator, idx);
        return -1;
    }

    if ( CYCLE[denominator][minus] > 0 ){
        int period = idx - CYCLE[denominator][minus];
        return period;
    }
    CYCLE[denominator][minus] = idx;
    // printf("\n call: %d %d %d %d\n", n, minus, denominator, idx);
    // Step1] 위: denominator*(n+minus), 아래: n - minus*minus
    assert((n-minus*minus)%denominator == 0);
    int down = (n-minus*minus)/denominator;
    // Step2 : Root(n)+minus / down 의 정수부가 다음 A
    int a = (sq_floor(n) + minus) / down;

    // printf("D: %d A: %d,",down, a);
    if (idx != 1) printf(",");
    printf("%d", a);
    return report_period(n, down*a - minus, down, idx+1);
}
int report(int n){
    int ret = 0;
    init_cycle();
    int a0 = sq_floor(n);
    printf("[%d",a0);
    if (a0*a0 != n){
        printf(";(");
        ret = report_period(n, a0, 1, 1);
        printf(")");
    }
    printf("]");
    printf(", period = %d", ret);
    printf("\n");
    
    return ret;
}

int main(){
    // report(23);
    // return 0;
    int cnt = 0;
    for (int i = 2 ; i<= 10000; ++i){
        printf("Root of %d = ", i);
        int r = report(i);
        assert(r != -1);
        if (r % 2 == 1) cnt++;
        // printf("%d %d\n", i, sq_floor(i));
    }
    printf("odd period count is %d\n", cnt);
}

