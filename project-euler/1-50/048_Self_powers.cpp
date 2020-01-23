#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

#define E10 10000000000
#define E5 100000

// overflow 7323401452
long long int exp(int a, int b){
    if (b == 0) return 1;
    if (b%2 == 1)
        return a * exp(a, b-1) % E10;
    long long int t = exp(a, b/2);
    // return t * t % E10; // t*t can produce overflow!!
    long long int t1 = (t / E5) * E5;
    long long int t2 = t % E5;
    return (2*(t1*t2) + t2*t2) % E10;
}
int main(){
    long long int sum;

    /*
    sum = 0;
    for (int i = 1 ; i <= 10 ; ++i)
        sum += exp(i,i);
    printf("%lld \n", sum % E10);
    */

    sum = 0;
    for (int i = 1 ; i <= 1000 ; ++i){
        sum += exp(i,i);
    }
    printf("%lld \n", sum % E10);
}



