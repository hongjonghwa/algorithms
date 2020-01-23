#include<stdio.h>

int sqrt(int n){
    double d = n;
    for (;;){
        double next = (d + n/d) / 2;
        // printf( "%d 's next is %f \n", n, next);
        if (d - next > - 0.01 && d - next < 0.01 ){
            // printf( "n 's sqrt is %f \n", next);
            return (int)(next + 0.01);
        }
        d = next;
    }
}
bool isPrime( int n ){
    if (n == 1) return false;
    if (n < 4) return true; // 2, 3
    if (n % 2 == 0) return false;
    if (n < 9) return true; // already excluded 4, 6 and 8
    if (n % 3 == 0) return false;
    int r = sqrt(n); // r * r <= n

    int f = 5;
    while(f<=r){
        if (n % f == 0) return false;
        if (n %(f+2) == 0) return false;
        f += 6;
    }
    return true;

}
int main(){
    int c = 0;
    for (int i = 1 ; i < 500 ; ++i){
    // for (int i = 1 ; i < 26 ; ++i){
        if (isPrime(i)) {
            printf("%d\n", i);
            c++;
        }

    }
    printf("prime count below 500 is %d \n", c);
}

