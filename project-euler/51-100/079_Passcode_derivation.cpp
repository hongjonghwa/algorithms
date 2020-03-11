
/*
 * 유사해보이지만 다른 알고리즘
 * - Shortest common supersequence
 * - De Bruijn sequence (cyclic)
 */

// Topological sorting 로 풀어보자
// - 전제 : Acyclic, DAG(Directed Acyclic Graph)

#include<stdio.h>

//int INPUT[];

char X[10][10];
bool exist[10];
char state[10]; // 0: has not been processed, 1: is under processing, 2: has been processed
char answer[100];
int answer_len = 0;

void dfs(int n){
    if (!exist[n]) return;
    if (state[n] == 1) printf("Cycle detected!");
    if (state[n] == 2) return;
    state[n] = 1;
    for (int i = 0 ; i < 10; ++i){
        if(X[n][i]) dfs(i);
    }
    answer[answer_len++] = n;
    state[n] = 2;
}

void topological_sorting(){
    for (int i = 0 ; i < 10 ; ++i)
        dfs(i);
    for (int i = answer_len - 1 ; i >= 0 ; --i)
        printf("%d", answer[i]);
    printf("\n");
}

int main(){
    freopen("p079_keylog.txt", "rt", stdin);
    char t[4];
    for (int i = 0 ; i < 50 ; ++i){
        scanf("%s", t);
        // printf("%s\n", t);
        X[t[0]-'0'][t[1]-'0']++;
        X[t[1]-'0'][t[2]-'0']++;
        X[t[0]-'0'][t[2]-'0']++;
        exist[t[0]-'0'] = exist[t[1]-'0'] = exist[t[2]-'0'] = true;
    }
    /*
    for (int y = 0 ; y < 10 ; ++y){
        for (int x = 0 ; x < 10 ; ++x)
            printf("%2d ", X[y][x]);
        printf("\n");
    }
    */
    topological_sorting();
    return 0;
}
