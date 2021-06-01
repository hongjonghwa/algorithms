#include<stdio.h>
#define MIN(a,b) (a)<(b)?(a):(b)

int T,N,V;
int X[101];
long long int P[101];

long long int solv(){
    // pre
    for (int i = 1 ; i <= N ; ++i)
        P[i] =  P[i-1] + X[i];

    long long int cost = P[N];
    int vv = V  - N;
    while ( vv  > 0){
        //printf( " vv -> %d\n", vv);
        int limit = MIN(vv, N);
        // find minimul
        int pick = 1;
        long long int best_nu = P[1], best_de = 1;
        for (int i = 2 ; i <= limit ; ++i)
            if ( P[i]*best_de < best_nu*i){
                pick = i;
                best_nu = P[pick];
                best_de = pick;
            }
        //printf( " pick  -> %d  %d/%d\n", pick, best_nu, best_de);
        // sub
        int set = vv / pick;
        vv -= (set * pick);
        cost += set * P[pick];
    }

    return cost;
}


int main(){
    freopen("input.txt", "rt", stdin);
    setbuf(stdout, NULL);
    scanf("%d", &T);
    for (int t = 1 ; t <= T ; ++t){
        scanf("%d%d", &N,&V);
        for (int i = 1 ; i <= N  ; ++i) 
            scanf("%d", &X[i]);
        long long int ret = solv();
        printf("#%d %lld\n", t, ret);
    }
    return 0;
}

