#include<cstdio>
int N, P, Q; // 1 ≤ P ≤ 10000 , 1 ≤ Q ≤ 100
int X[100];

 // WRONG!
int solv(int lo, int hi){
    if (lo >= hi) return 0;
  
    int best = -1, last = 987654321;
    for (int i = 0 ; i < Q; ++i){
        if (X[i] >= lo && X[i] <= hi ){
            int dist_from_mid = lo + hi - 2*X[i];
            if (dist_from_mid < 0) dist_from_mid = -dist_from_mid;
            if (last > dist_from_mid){
                last = dist_from_mid;
                best = X[i];
            }
        }
    }
    if (best == -1) return 0;

    return (hi - lo) + solv (lo, best -1) + solv(best+1, hi);
}

int main(){
    if (scanf("%d", &N) != 1) return 1;
    for (int t = 0 ; t < N ; ++t){
        if (scanf("%d%d", &P, &Q) != 2) return 1;
        for (int i = 0 ; i < Q ; ++i)
            if (scanf("%d", &X[i]) != 1) return 1;

        int ans = solv(1, P);
        printf("Case #%d: %d\n", t+1, ans);
    }
}