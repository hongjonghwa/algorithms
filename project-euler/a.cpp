/* 
 * https://en.wikipedia.org/wiki/Partition_(number_theory)
 * https://ko.wikipedia.org/wiki/%EC%9E%90%EC%97%B0%EC%88%98%EC%9D%98_%EB%B6%84%ED%95%A0
 * https://wiki.mathnt.net/index.php?title=%EC%9E%90%EC%97%B0%EC%88%98%EC%9D%98_%EB%B6%84%ED%95%A0%EC%88%98(integer_partitions)
 * https://namu.wiki/w/%EB%B6%84%ED%95%A0%EC%88%98
 * 
 */

#include<stdio.h>
#define MAX(a,b) (a)>(b) ? (a) : (b)
#define MIN(a,b) (a)<(b) ? (a) : (b)

#define NN 10000
int D[NN][NN];
int p(int n, int maximum){
    if (n == 0) return 1;
    if (D[n][maximum] > 0) return D[n][maximum];

    long long int sum = 0;

    // 몇 개를 집을까?
    for (int i = MIN(maximum, n); i ; --i)
        sum += p(n-i, i);

    return D[n][maximum] = sum % 1000000;
}
void solv_naive(){
    // 백만은 커녕, 십만도 어렵다
    for (int i = 1 ; i < NN ; ++i){
        long long int r = p(i,i);
        if (r % 10000 == 0) {
            printf("%d %lld\n", i, r);
            break;
        }
    }
}

int main(){
    solv_naive();
    for (int i = 1 ; i < 15 ; ++i){
        long long int r = p(i,i);
        printf("\t%d\t%lld\n", i, r);
    }
}
