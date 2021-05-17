#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int N, K;
vector<int> adj[501];
int bMatch[501];
bool aVisited[501];

bool dfs(int a){
    if(aVisited[a]) return false;
    aVisited[a] = true;
    for (auto b : adj[a]){
        if (bMatch[b] == 0 || dfs(bMatch[b])){
            bMatch[b] = a;
            return true;
        }
    }
    return false;
}

int bipartite(){
    int ret = 0;
    for (int i = 1 ; i < N+1; ++i){
        memset(aVisited, 0, sizeof(aVisited));
        if (dfs(i)) ++ret;
    }
    return ret;
}

int main(){
    cin >> N >> K;
    for (int i = 0 ; i < K ; ++i){
        int r, c;
        cin >> r >> c;
        adj[r].push_back(c);
    }
    cout << bipartite() << "\n";
}