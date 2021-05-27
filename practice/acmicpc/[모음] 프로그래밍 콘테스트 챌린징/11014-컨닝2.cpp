/*
https://codingcompetitions.withgoogle.com/codejam/round/00000000004329f5/000000000043314f
https://en.wikipedia.org/wiki/Independent_set_(graph_theory)


최대 독립 집합(Maximum Independent Set):  정점들을 가능한 한 많이 선택하되 선택된 정점끼리는 서로 인접하지 않게 되는 집합을 말합니다

그래프에서 
- 최대 독립 집합 + 최소 버택스 커버 = 전체 정점
- 최소버텍스커버 >= 최대매칭

이분 그래프에서
-  최소 버텍스 커버 = 최대 매칭 (쾨닉의 정리)
*/


#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

int DY[] = {-1,0,1,-1,0,1}, DX[] = {-1,-1,-1,1,1,1};

int T,N,M;
char MAP[80][81];

int visited[80][80];
int visitTrue = 0;
int matchY[80][80], matchX[80][80];

bool dfs(int y, int x){
    if (MAP[y][x] != '.' || visited[y][x] == visitTrue) return false;
    visited[y][x] = visitTrue;
    for (int d = 0 ; d < 6 ; ++d){
        int by = y+DY[d], bx = x+DX[d];
        if (by<0 || by>=N || bx<0 || bx>=M || MAP[by][bx]!='.') continue;
        if (matchY[by][bx] == -1 || dfs(matchY[by][bx], matchX[by][bx])){
            matchY[by][bx] = y, matchX[by][bx] = x; // b 매칭
            return true;
        }
    }
    return false;    
}

int bipartite(){
    memset(matchY,-1,sizeof(matchY));
    memset(matchX,-1,sizeof(matchX));
    int max_matching = 0;
    for (int y = 0 ; y < N ; ++y)
        for (int x = 0 ; x < M ; x+=2 ){
            visitTrue++;
            if (dfs(y,x)) max_matching++;
        }
    int node_cnt = 0;
    for (int y = 0 ; y < N ; ++y)
        for (int x = 0 ; x < M ; ++x )
            if (MAP[y][x] == '.')
                node_cnt++;
    return node_cnt - max_matching;
}

int main(){
    if (scanf("%d", &T) != 1) return 1;
    for (int t = 0 ; t < T ; ++t){
        if (scanf("%d%d", &N, &M) != 2) return 1;
        for (int y = 0 ; y < N ; ++y)
            if (scanf("%s", MAP[y]) != 1) return 1;
        printf("%d\n", bipartite());
    }
}