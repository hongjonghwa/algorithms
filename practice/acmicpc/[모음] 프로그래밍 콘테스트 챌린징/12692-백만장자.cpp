#include<cstdio>

int N, M, X;
double P;

double solv(){
    printf("%d %lf %d\n", M,  P, X);
    return 0;
}

int main(){
    if (scanf("%d", &N) != 1) return 1;

    for (int t = 0 ; t < N ; ++t){
        if (scanf("%d%lf%d", &M, &P, &X) != 3) return 1;
        double ans = solv();
        printf("%lf\n", ans);
    }
}