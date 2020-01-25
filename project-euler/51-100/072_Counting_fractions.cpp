#include<stdio.h>
#include<assert.h>

int minFactor[1000001];
void e(){
    for (int i = 1 ; i <= 1000000 ; ++i) minFactor[i] = i;
    for (int i = 2 ; i <= 1000; ++i){
        if (minFactor[i] == i)
            for (int j = i*i ; j <= 1000000 ; j += i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
    }
}

int gcd(int p, int q){
    return q == 0 ? p : gcd(q, p%q);
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

// bt 
int D;
int idx = 0;
int factors[7];

// 1 ~ D-1 중 소인수들의 배수가 되는 수의 갯수를 제한다
int bt(int i, int cnt, int mul){
    if (i == idx){
        int t = (D-1)/mul; //  1 ~ D-1 중 mul의 배수의 갯수
        if (cnt %2 == 1) t=-t; // 선택한 소인수가 짝수이면 +, 홀수이면 - (0일때는 1의 배수 임)
        //printf("cnt, mul, t : %d %d %d\n", cnt, mul, t);
        return t;
    }
    int ret = bt(i+1, cnt+1, mul*factors[i]);
    ret += bt(i+1, cnt, mul);
    return ret;
}

int count_proper_fraction_with_phi(int d) {
    if (minFactor[d] == d) return d-1;
    return phi(d);
}

int count_proper_fraction(int d) {
    D = d;
    if (minFactor[d] == d) return d-1;
    idx = 0;
    int last = 0;
    int dd = d;
    // 소인수 분해
    while (dd > 1){
        if (minFactor[dd] != last){
            last = factors[idx++] = minFactor[dd];
        }
        dd /= minFactor[dd];
    }
    return bt(0, 0, 1);
}

int count_proper_fraction2(int d) { // slow version
    int cnt = 0;
    for (int n = 1 ; n < d ; ++n)
        if (gcd(d, n) == 1)
            cnt++;
    return cnt;
}

int main(){
    e();

    for (int i = 1 ; i <= 100 ; ++i){
        assert(count_proper_fraction2(i) == count_proper_fraction(i));
        assert(count_proper_fraction2(i) == count_proper_fraction_with_phi(i));
    }

    long long int ret = 0;
    for (int i = 1 ; i <= 1000000; ++i){
        // ret += count_proper_fraction(i); // 0.12 sec
        ret += count_proper_fraction_with_phi(i); // 0.08 sec
    }
    printf("Answer is : %lld\n", ret);

}
