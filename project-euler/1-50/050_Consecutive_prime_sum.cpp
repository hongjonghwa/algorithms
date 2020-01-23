#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))


bool isPrime[1000000];
int P[1000000];
int L;
void e(){
    for (int i = 2 ; i < 1000000 ; ++i) isPrime[i] = true;
    for (int i = 2 ; i < 1000 ; ++i)
        if (isPrime[i])
            for (int j = i * i ; j < 1000000 ; j+=i)
                isPrime[j] = false;
}
int main(){
    e();
    for (int i = 1 ; i < 1000000 ; ++i)
        if (isPrime[i])
            P[L++] = i;

    int answer_cnt = 0;
    int answer_sum = 0;
    for (int i = 0 ; i < L ; ++i){
        int sum = 0, cnt = 0;
        for (int j = i ; j < L ; ++j){
            sum+=P[j];
            cnt++;
            if (sum >= 1000000) break;
            //printf("cnt:%d sum:%d\n", cnt, sum);
            if (isPrime[sum] && cnt > answer_cnt){
                printf("Debug: cnt:%d sum:%d s:%d(%d) e:%d(%d) \n", cnt, sum, i, P[i], j, P[j]);
                answer_cnt = cnt;
                answer_sum = sum;
            }
        }
    }
    printf("%d %d\n", answer_sum, answer_cnt);
}



