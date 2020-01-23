// 오일러 곱 공식(영어: Euler product formula)
// https://ko.wikipedia.org/wiki/%EC%98%A4%EC%9D%BC%EB%9F%AC_%ED%94%BC_%ED%95%A8%EC%88%98

#include<time.h>
#include<stdio.h>
#include<assert.h>
#define N 10000

int minFactor[10000001];
void e(){
    minFactor[0] = -1;
    minFactor[1] = -1;
    for (int i = 2 ; i <= 10000000 ; ++i) minFactor[i] = i;
    for (int i = 2 ; i <= 10000 ; ++i)
        if (minFactor[i] == i)
            for (int j = i * i ; j <= 10000000 ; j += i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
}

// 오일러 피 함수 - Euler’s phi (totient) function
int phi(int n){
    long long int ret = n;
    int lastFactor = -1;
    while (n > 1){
        if (minFactor[n] != lastFactor){
            lastFactor = minFactor[n];
            ret *= (minFactor[n]-1);
            ret /= minFactor[n];
        }
        n /= minFactor[n];
    }
    return int(ret);
}

bool is_permutation(int p, int q){
    int D[10] = {0,0,0,0,0,0,0,0,0,0};
    while (p>0){
        D[p%10]++;
        p/=10;
    }
    while (q>0){
        D[q%10]--;
        q/=10;
    }
    for (int i = 0 ; i < 10 ; ++i)
        if (D[i] != 0) 
            return false;
    return true;
}

int main(){
    e();
    double best = 1e100;
    for (int i = 2 ; i < 10000000; ++i){
        int pval = phi(i);
        if (is_permutation(i, pval)){
            double ratio = double(i) / pval;
            if (ratio < best){
                printf("%d => phi: %d, ratio %f \n", i, pval, ratio);
                best = ratio;
            }
        }
    }

}
