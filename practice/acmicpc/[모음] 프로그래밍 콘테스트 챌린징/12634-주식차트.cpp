#include<iostream>
#include<vector>
#include<cstring>
#define COMPARE(a,b) ((a)<(b)?-1:(a)>(b))

using namespace std;

int T,N,K;
int X[100][25];

vector<int> adj[100];
int D[100][100];
void make_edge(){
    for (int u = 0 ; u < N; u++)
        for (int v = 0 ; v < u ; v++){
            D[u][v] = COMPARE(X[u][0], X[v][0]);
            if (D[u][v] == 1){
                for (int k = 1 ; k < K ; ++k)
                    if (X[u][k] <= X[v][k]){
                        D[u][v] = 0;
                        break;
                    }
            }else if (D[u][v] == -1){
                for (int k = 1 ; k < K ; ++k)
                    if (X[u][k] >= X[v][k]){
                        D[u][v] = 0;
                        break;
                    }
            }
            D[v][u] = -D[u][v];
        }

    for (int u = 0 ; u < N; u++){
        adj[u].clear();
        for (int v = 0 ; v < N; v++)
            if (D[u][v] == -1) 
                adj[u].push_back(v);
    }
}

int visited[100];
int visitTrue = 0;
int bMatch[100];

bool dfs(int a){
    if (visited[a]==visitTrue) return false;
    visited[a] = visitTrue;
    for (auto b : adj[a]){
        if (bMatch[b] == -1 || dfs(bMatch[b])){
            bMatch[b] = a;
            return true;
        }
    }
    return false;
}

int bipartite(){
    memset(bMatch, -1, sizeof(bMatch));
    int ret = 0;
    for (int a = 0 ; a < N ; ++a){
        visitTrue++;
        if (dfs(a)) ret++;
    }
    return N-ret; // all - max_flow 
}


int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> T;
    for (int t=0 ; t < T ; ++t){
        cin >> N >> K;
        for (int y = 0 ; y < N ; ++y)
            for (int x = 0 ; x < K ; ++x)
                cin >> X[y][x];
        make_edge();
        int ans = bipartite();
        cout << "Case #" << (t+1) << ": " << ans << "\n";

    }
}