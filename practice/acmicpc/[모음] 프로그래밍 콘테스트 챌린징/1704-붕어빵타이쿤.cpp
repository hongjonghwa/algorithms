#include<cstdio>
#include<cstring>
#define INF 987654321

int M, N;
int X[17][17];
int A[16][16];
int best[16][16];
int last = INF;

void turnover(int y, int x){
    A[y][x] = !A[y][x];
    X[y][x] = !X[y][x];
    X[y][x-1] = !X[y][x-1];
    X[y][x+1] = !X[y][x+1];
    X[y-1][x] = !X[y-1][x];
    X[y+1][x] = !X[y+1][x];
}

void bt(int y, int x, int cnt){
    if (x == N+1) x = 1, y++;
    if (y == M+1){
        if (cnt>=last) return;
        for (int x = 1 ; x < N+1 ; ++x)
            if (X[M][x]) return;

        last = cnt;
        memcpy(best, A, sizeof(A));
        return;
    }

    if (y == 1){ // permutation
        bt(y, x+1, cnt);
        turnover(y,x);
        bt(y, x+1, cnt+1);
        turnover(y,x);
    }

    if (y > 1 && y <= M){
        // assert (1 < y <= M)
        int turn=0;
        if (X[y-1][x]) turn=1;
        if (turn) turnover(y,x);
        bt(y, x+1, cnt+turn);
        if (turn) turnover(y,x);
    }
    return;
}


void solv(){
    memset (A, 0, sizeof(A));
    bt(1,1,0);
    if (last < INF){
        for (int y = 1 ; y < M+1 ; ++y){
            for (int x = 1 ; x < N+1 ; ++x)
                printf("%d ", best[y][x]);
            printf("\n");
        }
    }
    else printf("IMPOSSIBLE\n");
}

int main(){
    if (scanf("%d%d", &M, &N) !=2 ) return 1;
    for (int y = 1 ; y < M+1 ; ++y)
        for (int x = 1 ; x < N+1 ; ++x)
            if (scanf("%d", &X[y][x]) != 1) return 1;
    solv();
}
