#include<stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

struct BigInt{
    int size, capa;
    unsigned int* x;
    BigInt(unsigned int initial = 0){
        capa = 4; // initial
        size = 1; 
        x = new unsigned int[capa];
        for (int i = 1 ; i < capa ; ++i) x[i] = 0;
        x[0] = initial;
    }
    void _expand(){
        int newcapa = capa * 2;
        unsigned int* xx;
        xx = new unsigned int[newcapa];
        for (int i = 0 ; i < capa ; ++i) xx[i] = x[i];
        for (int i = capa ; i < newcapa ; ++i) xx[i] = 0;
        delete[] x;
        x = xx;
        capa = newcapa;
    }
    void report(){
        printf("Size : %d(/%d) :", size, capa);
        for (int i = 0 ; i < size ; ++i)
            printf(" %d", x[i]);
        printf("\n");
    }
};
/*
BigInt operator+(BigInt lhs, BigInt rhs){
    int l = MAX(lhs.l, rhs.l);
    BigInt ret(0, l);
    for (int i = 0 ; 
    return BigInt(30);
}
*/

int sqroot(int n){
    int lo = 0, hi = n;
    while( lo + 1 < hi ){
        int mid = (lo+hi)/2;
        if (mid*mid > n) hi = mid;
        else lo = mid;
    }
    return lo;
}
void solv(int n){
    printf("# %d \n", n);
    int a0 = sqroot(n);
    if (a0*a0 == n) return; // skip
    int numerator = a0;
    int denominator = 1;
    printf("a0 is %d/%d %f \n", numerator, denominator, float(numerator)/denominator);

}
int main(){
    for (int i = 2 ; i < 3 ; ++i)
        solv(i);
}
