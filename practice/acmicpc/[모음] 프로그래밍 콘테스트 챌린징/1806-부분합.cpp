#include <cstdlib>
#include <cstdio>
#define INF 987654321

int N, S;
int X[100000];

int solv(){
    int best = INF;
    int sum = 0;
    for (int i = 0, j = 0; j < N ; ){
        while (sum < S && j < N)  sum += X[j++];
        while (sum >= S){
            if (j-i < best) best = j-i;
            sum -= X[i++];
        }
    }
    return best==INF ? 0 : best;
}

int main(){
    if (scanf("%d %d", &N, &S) != 2)
        return EXIT_FAILURE;
    for (int i = 0 ; i < N ; ++i)
        if (scanf("%d", &X[i]) != 1) 
            return EXIT_FAILURE;

    int ret = solv();
    printf("%d\n", ret);
}