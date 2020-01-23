#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

#define BN 20
#define E9 1000000000

struct bigint{
    unsigned int x[BN];
    bigint(){
        for (int i = 0; i < BN ; ++i) x[i] = 0;
    }
    bigint(unsigned int init){
        x[0] = init;
        for (int i = 1; i < BN ; ++i) x[i] = 0;
    }
    bigint multiply(bigint rhs){
        unsigned long long int c[BN];
        for (int i = 0; i < BN ; ++i) c[i] = 0;

        for (int i = 0 ; i < BN/2 ; ++i)
            for (int j = 0 ; j < BN/2 ; ++j)
                c[i+j] += ((unsigned long long int)x[i]) * rhs.x[j];
        
        for (int i = 0 ; i < BN - 1 ; ++i)
            if (c[i]>= E9){
                c[i+1] += c[i] / E9;
                c[i] %= E9;
            }

        bigint ret;
        for (int i = 0 ; i < BN ; ++i)
            ret.x[i] = c[i];
        // printf( " big int mul : %u\n", ret.x[0]);
        return ret;
    }
    bigint add(bigint rhs){
        bigint ret;
        for  (int i = 0 ; i < BN ; ++i)
            ret.x[i] = x[i] + rhs.x[i];
        for (int i = 0 ; i < BN - 1 ; ++i)
            if (ret.x[i]>= E9){
                ret.x[i+1] += ret.x[i] / E9;
                ret.x[i] %= E9;
            }
        // printf( " big int add : %u\n", ret.x[0]);
        return ret;
    }
    void report(){
        for (int i = BN - 1 ; i >= 0 ; --i)
            printf("%u ", x[i]);
    }
};

int ea(int n){
    if (n==0) return 2;
    if (n%3 == 2) return 2*(n+1)/3;
    return 1;
}
// root 2 for test
/*
int ea(int n){
    if (n==0) return 1;
    return 2;
}
*/
long long int gcd(long long int p, long long int q){
    return q==0 ? p : gcd(q, p%q);
}
struct fraction{
    bigint n, d;
    fraction(bigint numerator, bigint denominator){
        n = numerator;
        d = denominator;
    }
    fraction add(fraction rhs){
        bigint nn1 = d.multiply(rhs.n);
        bigint nn2 = n.multiply(rhs.d);
        bigint nn = nn1.add(nn2);
        bigint dd = d.multiply(rhs.d);
        // printf( " fraction add %u %u %u %u\n", nn1.x[0], nn2.x[0], nn.x[0], dd.x[0]);
        // long long int g = gcd(nn,dd); // 무한소수라 불필요
        return fraction (nn, dd);
    }
    fraction reverse(){
        return fraction(d,n);
    }
};
fraction calc(int n){
    /*
    1: a0 + 1/a1
    2: a0 + 1/(a1 + 1/a2)
    3: a0 + 1/(a1 + 1/(a2+1/a3))
    */
    fraction t(ea(n), 1);
    printf("[n: %d   fraction : %llu/%llu\n", n, t.n.x[0], t.d.x[0]);
    while (n--){
        t = t.reverse();
        //printf("re: %d   fraction : %llu/%llu\n", n, t.n.x[0], t.d.x[0]);
        t = t.add(fraction(ea(n),1) );
        printf(" n: %d   fraction : \n", n ) ;
        printf("     ");
        t.n.report();
        printf("\n");
        printf("     ");
        t.d.report();
        printf("\n");
    }
    //printf("gdb = %d\n", gcd(t.n, t.d));

    
    return t;
}
int main(){
    fraction ret = calc(99);

    int answer = 0;
    for (int i = 0 ; i < BN ; ++i){
        unsigned int t = ret.n.x[i];
        while (t>0){
            answer += t % 10;
            t /= 10;
        }
    }
    printf("answer is : %u\n", answer);
}

