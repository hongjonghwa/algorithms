// Reciprocal cycles (Problem 26)
// Reciprocal cycles II (Problem 417)
// https://en.wikipedia.org/wiki/Repeating_decimal
//
//
// 찾아볼 것
// https://www.nayuki.io/page/project-euler-solutions
// http://pipilupe.blogspot.com/2013/08/project-euler-problem-417.html

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int* X;
int recurCycle(int n){
    X[1] = 0;
    for (int i = 2 ; i < n ; ++i) X[i] = -1;

    int r = 1;
    for (int i = 1; i < n*2; ++i){
        r *= 10;
        r %= n;
        if (r==0) return 0;
        if (X[r] != -1) return i - X[r]; // no repeating decimal
        X[r] = i;
    }
    printf("something wrong!\n");
    return -1;
}

int main (){
    X = (int*)malloc(sizeof(int) * 100000000);
    printf("%lld\n", X);

    // problem 26
    /*
    long long int most = 0;
    int answer = 0;
    for (int i = 3 ; i <= 1000 ; ++i){
        int r = recurCycle(i);
        if (r > most) {
            most = r;
            answer = i;
        }
    }
    printf("%d\t%d\n", answer, most);
    */
    // problem 417
    long long int sum = 0;
    for (int i = 3 ; i <= 1000000 ; ++i){
        int r = recurCycle(i);
        sum += r;
    }
    printf("%lldd\n", sum);
    free(X);
}
