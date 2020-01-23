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
// bt 
int D;
int idx = 0;
int factors[7];
int bt(int i, int cnt, int mul){
    if (i == idx){
        int t = (D-1)/mul;
        if (cnt %2 == 1) t=-t;
        //printf("cnt, mul, t : %d %d %d\n", cnt, mul, t);
        return t;
    }
    int ret = bt(i+1, cnt+1, mul*factors[i]);
    ret += bt(i+1, cnt, mul);
    return ret;
}

int count_proper_fraction(int d) {
    D = d;
    if (minFactor[d] == d) return d-1;

    idx = 0;
    int last = 0;
    int dd = d;
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


    for (int i = 1 ; i <= 100 ; ++i)
        assert(count_proper_fraction2(i) == count_proper_fraction(i));

    long long int ret = 0;
    for (int i = 1 ; i <= 1000000; ++i)
        ret += count_proper_fraction(i);
    printf("Answer is : %lld\n", ret);

}
