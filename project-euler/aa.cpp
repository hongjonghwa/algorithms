#include<stdio.h>
#define N 10000

int gcd(int p, int q){
    return q == 0 ? p : gcd(q, p%q);
}
int phi[N+1];
int main(){
    /*
    for (int i = 2 ; i <= N ; ++i)
        phi[i] = i;
    for (int i = 2 ; i <= 10; ++i){
        for (int j = i ; j <= N ; j +=i)
            phi[j]--;
    }
    */
    for (int i = 2 ; i <= N; ++i){
        phi[i] = 1;
        for (int j = 2; j < i ; ++j)
            if (gcd(i,j) == 1)
                phi[i]++;
    }

    double best = 0;

    for (int i = 2 ; i <= N ; ++i){
        double d = double(i) / phi[i];
        if (d > best){
            printf("%d phi %d , %f\n", i, phi[i], d);
            best = d;
        }
    }

}
