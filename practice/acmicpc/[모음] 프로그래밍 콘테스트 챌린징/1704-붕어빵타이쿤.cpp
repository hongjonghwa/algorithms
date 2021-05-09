#include<cstdio>
#include<cstring>

int M, N;
int X[17][17];
int A[16][16];

void turnover(int y, int x){
    A[y][x] = !A[y][x];
    X[y][x] = !X[y][x];
    X[y][x-1] = !X[y][x-1];
    X[y][x+1] = !X[y][x+1];
    X[y-1][x] = !X[y-1][x];
    X[y+1][x] = !X[y+1][x];
}

bool bt(int y, int x){
    if (x == N+1) x = 1, y = y+1;
    if (y == M+1){
        bool ok = true;
        for (int x = 1 ; x < N+1 ; ++x)
            if (X[M][x]) {
                ok = false;
                break;
            }
        return ok;
    }

    if (y == 1){
        if (bt(y, x+1)) return true;
        turnover(y,x);
        if (bt(y, x+1)) return true;
        turnover(y,x);

        return false;
    }

    if (y > 1 && y <= M){
        // assert (1 < y <= M)
        bool turn=false;
        if (X[y-1][x]){
            turn=true;
            turnover(y,x);
        }
        if (bt(y, x+1)) return true;
        if (turn) turnover(y,x);
    }
    return false;
}


void solv(){
    int ret = bt(1,1);
    if (ret){
        for (int y = 1 ; y < M+1 ; ++y){
            for (int x = 1 ; x < N+1 ; ++x){
                if (x) printf(" ");
                printf("%d", A[y][x]);
            }
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
