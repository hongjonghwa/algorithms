#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int X[20][20];
void report_map(const char * str, int map[20][20]){
    // map
    printf("[%s]\n", str);
    for (int y = 0 ; y < N ; ++y){
        for (int x = 0 ; x < N ; ++x)
            printf("%d ", map[y][x]);
        printf("\n");
    }
}

int DISTANCE[20][20];
int DY[4] = {-1,1,0,0};
int DX[4] = {0,0,-1,1};
void bfs(int init_y, int init_x, int w){
    for (int y = 0 ; y < N ; ++y)
        for (int x = 0 ; x < N ; ++x)
            DISTANCE[y][x] = 9999;

    queue<pair<int,int>> que;
    DISTANCE[init_y][init_x] = 0;
    que.push(make_pair(init_y,init_x));

    while(!que.empty()){
        pair<int, int> here = que.front();
        que.pop();

        int y = here.first;
        int x = here.second;
        for (int i = 0 ; i < 4 ; ++i){
            int next_y = y + DY[i];
            int next_x = x + DX[i];
            if (next_y < 0 || next_y >= N || next_x < 0 || next_x >= N) continue;
            if (X[next_y][next_x] > w) continue;

            if (DISTANCE[next_y][next_x] > DISTANCE[y][x] + 1 ){
                DISTANCE[next_y][next_x] = DISTANCE[y][x] + 1;
                que.push(make_pair(next_y, next_x));
            }
        }

    }
}

int solv(){
    int ret = 0; // time
    int w = 2, remain = 2; // 크기, 남은 먹이 수

    int pos_y = -1, pos_x = -1; // 현재 위치
    for (int y = 0 ; y < N ; ++y){
        for (int x = 0 ; x < N ; ++x){
            if (X[y][x] == 9){
                pos_y = y;
                pos_x = x;
                X[pos_y][pos_x] = 0;
                break;
            }
        }
        if (pos_y != -1) break;
    }
    for (;;){
        bfs(pos_y, pos_x, w);
        //report_map("BFS", DISTANCE);

        // 가장 가까운 먹이를 찾고
        int find_y = -1, find_x = -1, best = 9999;
        for (int y = 0 ; y < N; ++y)
            for (int x = 0 ; x < N ; ++x){
                if (X[y][x] != 0 && X[y][x] < w && DISTANCE[y][x] < best){
                    best = DISTANCE[y][x];
                    find_y = y;
                    find_x = x;
                }
            }
        if (find_y == -1)
            return ret;

        ret += DISTANCE[find_y][find_x];
        X[find_y][find_x] = 0;
        remain--;
        if (remain == 0){
            w++;
            remain = w;
        }
        // printf("_DEBUG: Y(%d), X(%d), D(%d), W(%d), R(%d) \n" , find_y, find_x, DISTANCE[find_y][find_x], w, remain);
        pos_y = find_y;
        pos_x = find_x;
    }
}

int main(){
    // if ( freopen("input.txt", "r", stdin) == 0 ) return 255;
    if ( scanf("%d", &N) != 1) return EXIT_FAILURE ;

    for (int y = 0 ; y < N ; ++y)
        for (int x = 0 ; x < N ; ++x)
            if (scanf("%d", &X[y][x]) != 1) return EXIT_FAILURE ;
    // report_map("initial", X);

    int ret = solv();
    printf("%d\n", ret);
}
