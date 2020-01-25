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

// bt 
int D;
int idx = 0;
int factors[7];
int bt(int i, int cnt, int mul){
    if (i == idx){
        // 1 ~ D-1 이 아닌, 1/2 ~ 1/3 사이의 수
        int rh = (D-1)/2/mul;
        int lh = (D)/3/mul;
        int t= rh - lh;
        //if (cnt %2 == 1) t=-t; // 포함 배제 원리: 짝수로 판별하는 방법
        return t;
    }

    // 포함 배제 원리: inclusion–exclusion principle
    int ret = bt(i+1, cnt, mul);
    ret -= bt(i+1, cnt+1, mul*factors[i]); // 사실 이 방법에서는 cnt 를 넘겨 줄 필요가 없음
    return ret;
}

int count_proper_fraction(int d) {
    D = d;
    // 빠른 계산
    /* (없어도 무방, 큰 차이  없음)
    if (minFactor[d] == d) return int((D-1)/2) - int(D/3);
    */

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

int main(){
    e();

    long long int ret = 0;
    for (int i = 1 ; i <= 12000; ++i){
        int t = count_proper_fraction(i);
        ret += t;
        // printf( "%d %d\n", i, t);
    }
    printf("Answer is : %lld\n", ret);
    return 0;

}
