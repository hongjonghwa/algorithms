#include<stdio.h>
#include<string.h>
#define MAX(a,b) ((a)>(b) ? (a) : (b))

int T,N,M;
int MAP[10];
int D[10][1024];

int BCNT[1024];
void init(){
    int b = 1;
    for (int i = 0 ; i < 10 ; ++i){
        for (int j = 0 ; j < 1024 ; ++j)
            if (j&b) BCNT[j]++;
        b<<=1;    
    }
}

int dp(){
    memset(D, 0, sizeof(D));
    int DD = 1<<M;
    for (int i = 0 ; i < DD ; ++i){
        if ( (MAP[0]&i) > 0 || (i &(i<<1)) > 0) continue;
        D[0][i] = BCNT[i];
    }
    for (int i = 1 ; i < N ; ++i){
        for (int j = 0 ; j < DD; ++j){
            if ( (MAP[i]&j) > 0 || (j &(j<<1)) > 0) continue;
            for (int k = 0 ; k < DD; ++k){
                if ((k&(j<<1)) > 0 || (k&(j>>1)) > 0) continue;
                D[i][j] = MAX(D[i][j], D[i-1][k]);
            }
            D[i][j] += BCNT[j];
        }
    }

    int ret = 0;
    for (int i = 0 ; i < DD ; ++i)
        ret = MAX(ret, D[N-1][i]);
    return ret;
}

int main(){
    init();
    if (scanf("%d", &T) != 1) return 1;
    for (int t = 0 ; t < T ; ++t){
        if (scanf("%d%d", &N, &M) != 2) return 1;
        char buf[20];
        for (int y = 0 ; y < N ; ++y){
            if (scanf("%s", buf) != 1) return 1;
            int row = 0;
            for (int x = 0 ; x < M ; ++x){
                row <<= 1;
                if (buf[x] == 'x') row++;
            }
            MAP[y] = row;
        }
        printf("%d\n", dp());
    }
}