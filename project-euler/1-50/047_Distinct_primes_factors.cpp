#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int minFactor[1000001];
int number_of_factors(int n){
    int ret = 0;
    int last = 0;
    while (n > 1){
        if (minFactor[n] != last){
            last = minFactor[n];
            ret++;
        }
        n /= minFactor[n];
    }
    return ret;
}
void e(){
    for (int i = 2 ; i <= 1000000 ; ++i) minFactor[i] = i;
    for (int i = 2 ; i <= 1000 ; ++i)
        if (minFactor[i] == i)
            for (int j = i * i ; j <= 1000000 ; j+=i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
}

int main(){
    e();
    // int c = 0;
    int cont = 0;
    for (int i = 2 ; i <= 1000000 ; ++i) {
        //printf("%d %d\n", i, minFactor[i]);
        int factors = number_of_factors(i);
        printf("%d ==> %d , %d \n", i, factors, minFactor[i] == i);
        if (factors == 4) cont++;
        else cont = 0;
        if (cont == 4) break;
    }
}



