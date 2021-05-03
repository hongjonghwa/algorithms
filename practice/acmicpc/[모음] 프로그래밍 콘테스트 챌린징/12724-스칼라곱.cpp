#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

int T;
int N;
int X[2][800];

long long int solv(){
    sort(X[0], X[0]+N);
    sort(X[1], X[1]+N);
    long long int ret = 0;
    for (int i = 0 ; i < N ; ++i)
        ret += (long long int)X[0][i] * X[1][N-i-1];

    return ret;
}

int main(){
    if (scanf("%d", &T) != 1) return EXIT_FAILURE;
    for (int t = 0 ; t < T ; ++t){
        if (scanf("%d", &N) != 1) return EXIT_FAILURE;
        for (int i = 0 ; i < N ; ++i)
            if (scanf("%d", &X[0][i]) != 1) return EXIT_FAILURE;
        for (int i = 0 ; i < N ; ++i)
            if (scanf("%d", &X[1][i]) != 1) return EXIT_FAILURE;
        long long int ans = solv();
        printf("Case #%d: %lld\n", t+1, ans);
    }

}
