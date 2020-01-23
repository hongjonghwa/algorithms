#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

bool isPrime[100000001];
void e(){
    for (int i = 2 ; i <= 100000000 ; ++i) isPrime[i] = true;
    for (int i = 2 ; i <= 10000 ; ++i)
        if (isPrime[i])
            for (int j = i * i ; j <= 100000000 ; j += i)
                isPrime[j] = false;
}
int X[10000][2];
int L = 0;
int D[5];
int best = 987654321;
void bt(int idx){
    if (idx == 5){
        printf( "SUCCESS!");
        for (int i =0 ; i < 5; ++i)
            printf (" %d", X[D[i]][0]);
        printf("\n");

        int sum = 0;
        for (int i = 0 ; i < 5 ; ++i)
            sum += X[D[i]][0];
        if (sum < best) best = sum;
        return;
    }
    int st = idx == 0 ? 0 : D[idx-1] + 1;
    for (int i = st ; i < L ; ++i){
        bool candidate = true;
        for (int j = 0 ; j < idx ; ++j){
            int c = D[j];
            int next1 = X[c][0] + X[c][1]*X[i][0];
            int next2 = X[i][0] + X[i][1]*X[c][0];
            /*
            printf ("  --> next : %d %d %d %d %d %d \n", 
                    X[i][0], X[c][0], 
                    next1, next2, 
                    isPrime[next1], isPrime[next2]);
                    */
            if (!isPrime[next1] || !isPrime[next2]){
                // printf("FAIL!\n");
                candidate = false;
                break;
            }
        }
        if (candidate){
            // printf("pick %d %d %d candidate:%d\n", idx, i, X[i][0], candidate);
            D[idx] = i;
            bt(idx+1);
        }
    }
}

int main(){
    e();
    int exp = 10;
    for (int i = 2 ; i < 10000 ; ++i)
        if (isPrime[i]){
            X[L][0] = i;
            while (exp<i){
                exp *= 10;
            }
            X[L][1] = exp;
            L++;
        }
    printf("Len : %d\n", L);
    // for (int i = 0 ; i < 30 ; ++i) printf("%d %d\n", X[i][0], X[i][1]);
    bt(0);
               
    printf("Answer is %d\n", best);
}

