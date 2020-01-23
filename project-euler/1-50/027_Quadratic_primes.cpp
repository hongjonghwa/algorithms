#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int* X;
bool isPrime[1000001];
int primeUnder1000[168];
bool D[2001][168];
void erastothenes(){
    for (int i = 2 ; i <= 1000000 ; ++i) isPrime[i] = true;
    for (int i = 2 ; i <= 1000 ; ++i)
        if (isPrime[i])
            for (int j = i*i ; j <= 1000000 ; j += i)
                isPrime[j] = false;
}
void solv(){
    int a_min = -1000;
    for (int n = 1 ; n <= 100 ; ++n){
        printf("n's %d \n", n);
        int possible = false;
        for (int i = 0 ; i < 168 ; ++i){
            int b = primeUnder1000[i];
            // printf("b is %d %d \n", b, i);
            for (int a= -1000 ; a <= 1000 ; ++a){
                if (D[a+1000][i]) continue;
                int v = n*n + a*n + b;
                if (v <= 1 || v >= 1000000 || isPrime[v] == false){
                    D[a+1000][i] = true;
                    //printf("Impossible %d %d %d \n", n, a, b);
                }else{
                    possible = true;
                    printf("n=%d, b=%d, a=%d, v=%d isPrime %d\n", n, b, a, v, isPrime[v]);
                }
            }
        }
        if (possible == false){
            printf("can't preceed n = %d \n", n);
            break;
        }
        //break;
    }
}

int main (){
    erastothenes();
    int c = 0;
    for (int i = 2 ; i <= 1000 ; ++i)
        if (isPrime[i]){
            primeUnder1000[c++] = i;
            //printf("%d %d\n", c, i);
        }
    // return 0;
    //for (int i = 0 ; i < 168 ; ++i) printf("%d %d\n", i+1, primeUnder1000[i]);

    solv();

}
