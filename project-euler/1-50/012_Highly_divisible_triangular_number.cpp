#include<stdio.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAXN 20000
int TN[MAXN+1];

int getSqRoot(int n){
    if (n==1) return 1;
    double last = n/2;
    for (;;){
        double next = (n/last + last) /2;
        //printf("last - next %f - %f \n", last, next);
        if ( ABS(last - next) < 0.01) return int(next + 0.01);
        last = next;
    }
}
int getNumberOfDivisors(int n){
    int ret = 0;
    int sq = getSqRoot(n);
    // printf ("%d 's sqroot is %d", n, sq);
    for (int i = 1 ; i < sq ; ++i)
        if (n % i == 0) ret++;
    ret *= 2;
    if (sq * sq == n) ret++;
    return ret;
}
int solv1 (){
    int tn = 0;
    for (int i = 1 ; i <= MAXN ; ++i){
        tn+=i;
        int r = getNumberOfDivisors(tn);
        if (r > 500){
            return tn;
            break;
        }
    }
    return -1;
}
int D2[65501]; // number of divisors
int solv2() {
    for (int i = 1 ; i  <= 65500 ; ++i) D2[i] = 0;
    for (int i = 1 ; i <= 65500; ++i)
        for ( int j = i ; j <= 65500 ; j += i)
            D2[j] += 1;
    /*
    int most = -1;
    for (int i = 1 ; i <= 65500 ; ++i)
        if (most < D2[i]) most = D2[i];
    return most;
    */
    int tn;
    for (int i = 1 ; i <= MAXN ; ++i){
        tn = i * (i+1) / 2;
        int r;
        if (i % 2 == 0){ // even
            r = D2[i/2] * D2[i+1];
        }else{ // odd
            r = D2[i] * D2[(i+1)/2];
        }
        if (r > 500){
            return tn;
            break;
        }
    }
    return -1;
}
int minFactor[65501]; // minimal factor 소수인 경우 자기 자신...
int minFactorPower[65501]; // 소인수 분해 후 minFactor 가 몇 개인가 
int factors[65501]; // number of divisors
int solv3() {
    // minimal factor 계산
    minFactor[0] = minFactor[1] = -1; // 1은 예외 처리 => -를 붙이면, 실수로 사용하여도 발견하기 쉽다.
    for (int i = 2 ; i <= 65500 ; ++i) minFactor[i] = i; // 자기 자신으로 초기화
    int sqrtn = getSqRoot(65500);
    for (int i = 2 ; i <= sqrtn ; ++i){
        if (minFactor[i] == i) { // 소수이면
            for (int j = i * i ; j <= 65500 ; j += i)
                if (minFactor[j] == j) 
                    minFactor[j] = i;
        }
    }
    // divisors 수 계산
    factors[1] = 1;
    for (int n = 2 ; n <= 65500 ; ++n){
        if (minFactor[n] == n){
            minFactorPower[n] = 1;
            factors[n] = 2;
        }else{
            int p = minFactor[n];
            int m = n / p;
            if (p != minFactor[m])
                minFactorPower[n] = 1;
            else
                minFactorPower[n] = minFactorPower[m] + 1;
            int a = minFactorPower[n];
            factors[n] = (factors[m] / a) * (a+1);
        }
    }
    /*
    int most = -1;
    for (int i = 1 ; i <= 65500 ; ++i)
        if (most < factors[i]) most = factors[i];
    return most;
    */
    int tn;
    for (int i = 1 ; i <= MAXN ; ++i){
        tn = i * (i+1) / 2;
        int r;
        if (i % 2 == 0){ // even
            r = D2[i/2] * D2[i+1];
        }else{ // odd
            r = D2[i] * D2[(i+1)/2];
        }
        if (r > 500){
            return tn;
            break;
        }
    }
    return -1;
}
int main (){
    //freopen("data.txt", "rt", stdin);
    long long int clk;

    /* solv1: square-root 까지 디바이더의 갯수를 확인하여 2 배수 */

    clk = clock();
    printf ("solv1 : %d \n", solv1());
    printf (" = execution times : %f \n", (double)(clock() - clk) / CLOCKS_PER_SEC );

    clk = clock();
    printf ("solv1 : %d \n", solv1());
    printf (" = execution times : %f \n", (double)(clock() - clk) / CLOCKS_PER_SEC );

    /* solv2: 소인수 분해 */

    clk = clock();
    printf ("solv2 : %d \n", solv2());
    printf (" = execution times : %f \n", (double)(clock() - clk) / CLOCKS_PER_SEC );

    clk = clock();
    printf ("solv2 : %d \n", solv2());
    printf (" = execution times : %f \n", (double)(clock() - clk) / CLOCKS_PER_SEC );

    /* solv3: divisor 의 갯수 brutal force */

    clk = clock();
    printf ("solv3 : %d \n", solv3());
    printf (" = execution times : %f \n", (double)(clock() - clk) / CLOCKS_PER_SEC );

    clk = clock();
    printf ("solv3 : %d \n", solv3());
    printf (" = execution times : %f \n", (double)(clock() - clk) / CLOCKS_PER_SEC );

    //printf("answer is %lld \n", maxsum);
}
