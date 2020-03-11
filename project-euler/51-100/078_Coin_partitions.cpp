/* 
 * https://en.wikipedia.org/wiki/Partition_(number_theory)
 * https://ko.wikipedia.org/wiki/%EC%9E%90%EC%97%B0%EC%88%98%EC%9D%98_%EB%B6%84%ED%95%A0
 * https://wiki.mathnt.net/index.php?title=%EC%9E%90%EC%97%B0%EC%88%98%EC%9D%98_%EB%B6%84%ED%95%A0%EC%88%98(integer_partitions)
 * https://namu.wiki/w/%EB%B6%84%ED%95%A0%EC%88%98
 * 
 * https://en.wikipedia.org/wiki/Pentagonal_number_theorem
 */

#include<stdio.h>
#include<assert.h>

#define N 100000
#define PENTA_N 1000
#define MOD 10000000

int PENTA[PENTA_N];
int PENTA_MAX;
int pentagon_number(int n){
    return n * (3*n -1)  / 2;
}
// 기본형 
int partition_number(int n){
    if (n == 0) return 1;
    int ret = 0;
    for (int i = 0 ; PENTA[i] <= n ; ++i){
        if ( (i&2) == 0) // 0, 1, 4, 5, 8, 9, ...
            ret += partition_number(n-PENTA[i]) ;
        else
            ret -= partition_number(n-PENTA[i]);
    }
    return ret;
}

int D[N+1];
int partition_number_dp(int n){
    if (n >= PENTA_MAX){ // n > PENTA_MAX 이면,  PENTA_MAX == n 일 때 termination 지점이 안 생긴다
        printf("Not computable %d. (PENTA_MAX is %d.)\n", n, PENTA_MAX);
        return -1;
    }
    if (D[n] > 0 ) return D[n];

    int ret = 0;
    for (int i = 0 ; PENTA[i] <= n ; ++i){
        if ( (i&2) == 0){// 0, 1, 4, 5, 8, 9, ...
            // if (n == 40) printf(" + p(n-%d) ", PENTA[i]);
            ret += partition_number_dp(n-PENTA[i]) ;
        } else {
            //if (n == 40) printf(" - p(n-%d) ", PENTA[i]);
            ret -= partition_number_dp(n-PENTA[i]);
        }
    }
    D[n] = ret % MOD;
    if (D[n]<0) D[n] += MOD;
    return D[n];
}
int main(){
    for (int i = 1 ; i <= PENTA_N/2; ++i){
        PENTA[(i-1)*2] = pentagon_number(i);
        PENTA[(i-1)*2+1] = PENTA_MAX = pentagon_number(-i);
    }
    printf("### PENTA_MAX is %d (%d th)\n", PENTA_MAX, PENTA_N);
    /*
    for (int i = 1 ; i <=  10; ++i)
        printf("### partition number of %d is %d\n", i, partition_number(i));
    */

    D[0] = 1;
    for (int i = 1 ; i <= N ; ++i){
        int r = partition_number_dp(i);
        if (r == -1) break;
        if (r % 1000000 == 0) {
            printf("Answer : %d ( MOD VALUE: %d )\n", i, r);
            break;
        }
    }
    return 0;


}
