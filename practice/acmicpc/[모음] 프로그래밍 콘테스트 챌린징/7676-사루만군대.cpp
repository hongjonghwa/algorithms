#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

int R, N;
int X[1000];

int solv(){
    sort(X, X+N);
    int ret = 0;
    int l = -9999, palantir=-9999;
    for (int i = 0 ; i < N ; ++i){
        if (X[i] <= l + R)
            palantir = X[i]; // pass a palantir

        if (X[i] > palantir + R){ // needs palantir
            l = palantir = X[i];
            ret++;
        }
    }

    return ret;
}

int main(){
    for (;;){
        if (scanf("%d%d", &R, &N) != 2) return EXIT_FAILURE;
        if (R==-1 && N == -1) break;

        for (int i = 0 ; i < N ; ++i){
            if (scanf("%d\n", &X[i]) != 1) return EXIT_FAILURE;
        }
        int ret = solv();
        printf("%d\n", ret);
    }

}