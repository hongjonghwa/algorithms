// prob 69
// 정답은 따로 있다. 해설 PDF 봐라
// 오일러 곱 공식(영어: Euler product formula)
// https://ko.wikipedia.org/wiki/%EC%98%A4%EC%9D%BC%EB%9F%AC_%ED%94%BC_%ED%95%A8%EC%88%98

#include<time.h>
#include<stdio.h>
#include<assert.h>
#define N 10000

int minFactor[1000001];
void e(){
    minFactor[0] = -1;
    minFactor[1] = -1;
    for (int i = 2 ; i <= 1000000 ; ++i) minFactor[i] = i;
    for (int i = 2 ; i <= 1000 ; ++i)
        if (minFactor[i] == i)
            for (int j = i * i ; j <= 1000000 ; j += i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
}

int gcd(int p, int q){
    return q == 0 ? p : gcd(q, p%q);
}
int phi[1000001];
bool check (int p, int q){
    // method 2 : factor 중 같은 숫자가 있는지 
    for (;;){
        int pmin = minFactor[p], qmin = minFactor[q];
        if (pmin == qmin) return pmin == 1;
        if (pmin < qmin) {
            if (p == pmin) return true;
            p /= pmin;
        }
        else{
            if (q == qmin) return true;
            q /= qmin;
        }
    }
    assert(false); // impossible!
    // 서로 소인지 
    return gcd(p, q) == 1; // 서로소
}
int calc(int p){
    // 소수인 경우 자신보다 작은 모든 수와 서로 소
    if (p == minFactor[p]) return p-1;
    // 서로 소인것 확인
    int ret = 1;
    for (int i = 2; i < p ; ++i)
        if (check(i,p))
            ret++;
    return ret;
}
int get_factors(int p, int result[8]){
    int cnt = 0;
    int lastFactor = -1;
    while (p != 1){
        if (lastFactor != minFactor[p]) {
            result[cnt] = minFactor[p];
            cnt++;
        }
        lastFactor = minFactor[p];
        p /= minFactor[p];
    }
    return cnt;
}
void sel(int &ret, int p, int delta, int factors[8], int len, int idx, int topick, int val){
    if (idx == len){
        //printf("p = %d val %d delta %d\n", p, val, delta);
        ret += ((p-1)/val) * delta;
        return;
    }
    if (topick > 0) 
        sel(ret, p, delta, factors, len, idx+1, topick-1, val*factors[idx]);
    if (len-idx > topick)
        sel(ret, p, delta, factors, len, idx+1, topick, val);
} 

// 약수로 만들 수 있는 자신보다 작은 수의 갯수(서로 소인 수)를 먼저 계산해서 남은 수를 구함
int calc2(int p){
    // 소수인 경우 자신보다 작은 모든 수와 서로 소
    if (p == minFactor[p]) return p-1;

    int factors[8];
    int len = get_factors(p, factors);
    int ret = 0;
    for (int i = 1 ; i <= len ; ++i){
        int delta = i%2 == 1 ? 1 : -1; // 홀+ 짝-
        sel(ret, p, delta, factors, len, 0, i, 1);
    }
    return p-1-ret;
}
int count_factors(int p){
    int cnt = 0;
    int lastFactor = -1;
    while (p != 1){
        if (lastFactor != minFactor[p]) cnt++;
        lastFactor = minFactor[p];
        p /= minFactor[p];
    }
    return cnt;
}
int main(){
    e();
    /* 
    // how many factors required under 1e6 
    int c = 0, s = 1;
    for (int i = 2 ; i < 100 ; ++i)
        if (minFactor[i] == i){
            printf ("[%d] %d => %d\n", ++c, i, s*=i);
        }
    */

    /*
    // numbers having 7 factors
    for (int i = 2 ; i<= 1000000; ++i){
        int c = count_factors(i);
        if (c >= 7) printf(" %d's factors %d \n", i, c);
    }
    */

    long long int clk = clock();

    for (int i = 2 ; i <= 1000000 ; ++i)
        phi[i] = calc2(i);

    printf("Execution time : %f \n", (double(clock())-clk)/CLOCKS_PER_SEC);

    double best = 0;

    for (int i = 2 ; i <= 1000000 ; ++i){
        double d = double(i) / phi[i];
        // printf("%d phi %d , %f\n", i, phi[i], d);
        if (d > best){
            printf("%d phi %d , %f\n", i, phi[i], d);
            best = d;
        }
    }

}
