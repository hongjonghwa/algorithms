#include<cstdio>

int N, K;
int X[10000]; //  1 meter - 100 kilometers (100*1000*100 cm)

bool check(int n){
    int cnt = 0;
    for (int i = 0 ; i < N ; ++i)
        cnt += X[i] / n;
    return  cnt >= K;
}

int solv(){
    int lo = 0, hi = 10000001;
    // lo 는 가능 , hi 는 불가
    while (lo + 1 < hi){
        int m = (lo + hi)/2;
        if (check(m)) lo = m;
        else hi =m;
    }
    return lo;
}

int main(){
    if (scanf("%d%d", &N, &K) != 2) return 1;
    for (int i = 0; i < N ; ++i){
        double l;
        if (scanf("%lf", &l) != 1) return 1;
        X[i] = (int)(l*100); // 실수 오차를 고려해야 할까?
    }
    int ans = solv();
    printf("%.2f" , (double)ans/100);
}