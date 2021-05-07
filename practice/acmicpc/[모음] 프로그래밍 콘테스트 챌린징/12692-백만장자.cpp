#include<cstdio>
#include<cstring>
#include<cassert>

template<class T>
inline T min(const T a, const T b){
    return a<b ? a : b;
}

int T;

double D[16][(1<<15) + 1];
double solv(int round, double prob, int starting){
    // printf("%d %lf %d\n", round,  prob, starting);
    int n = (1<<round);
    memset(D[0], 0, sizeof(D[0]));
    D[0][n] = 1.0;
    for (int r = 1 ; r <= round ; ++r){
        assert(n < (1<<15) + 1);
        D[r][n] = 1.0;
        for (int i = 0 ; i < n ; ++i){
            D[r][i] = 0;
            int j_max = min(i, n-i);
            for (int j = 0; j <= j_max ; j++){
                double t = prob*D[r-1][i+j] + (1-prob)*D[r-1][i-j];
                if (t>D[r][i]) D[r][i] = t;
            }
        }
    }

    // for (int i =0 ; i <= n ; ++i) printf(" - %d %lf\n", i, D[round][i]);

    if (starting >= 1000000) return 1;

    return D[round][starting * n / 1000000];
}

int main(){
    if (scanf("%d", &T) != 1) return 1;

    for (int t = 0 ; t < T ; ++t){
        int n, x;
        double p;
        if (scanf("%d%lf%d", &n, &p, &x) != 3) return 1;
        double ans = solv(n, p, x);
        printf("Case #%d: %lf\n", t+1, ans);
    }
}