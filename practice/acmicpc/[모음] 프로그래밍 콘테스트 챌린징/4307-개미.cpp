#include <cstdio>
#include <cstdlib>
#define SWAP(a,b) {int tmp=a;a=b;b=tmp;}
#define MAX(a,b) ((a)>(b)?(a):(b))

int T, L, N;
int X[100000];
void solv(){
    int fastest = 0;
    int lastest = 0;
    for (int i = 0 ; i < N ; ++i){
        int l = X[i], u = L-X[i];
        if (l>u) SWAP(l,u);
        fastest = MAX(fastest, l);
        lastest = MAX(lastest, u);        
    }
    printf("%d %d\n", fastest, lastest);
}
int main(){
    if (scanf("%d", &T) != 1) return EXIT_FAILURE;
    for (int t = 0 ; t < T ; ++t){
        if (scanf("%d%d", &L, &N) != 2) return EXIT_FAILURE;
        for (int i = 0 ; i < N ; ++i)
            if (scanf("%d", &X[i]) != 1) return EXIT_FAILURE;
        solv();
    }
}