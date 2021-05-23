/*
# note
A:사람 -> B: (탈출가능한 시간 순서대로) 출구번호 로 매칭하니 dfs 를 최댄거리 먼저 돌리기 어려웠음.
최단거리 매칭을 우선하기 위해 A:각시간의출구 -> B:가까운 사람 으로 변경
*/

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int N, K;
char MAP[13][13];
vector<pair<int, int>> EXIT;
int DY[4] = {1,-1,0,0 }, DX[4] = {0,0,1,-1};

vector<vector<pair<int,int>>> adj;
// vector<int> aMatch;
vector<int> bMatch;

bool dfs(int a, vector<bool> &visited, int &max_a_node){
    if (visited[a]) return false;
    visited[a]= true;
    
    for (unsigned i = 0 ; i < adj[a].size() ; ++i){
        int b = adj[a][i].second;
        if (bMatch[b] == -1 || dfs(bMatch[b], visited, max_a_node)){
            if (a > max_a_node) max_a_node = a;
            // aMatch[a] = b;
            bMatch[b] = a;
            return true;
        }
    }
    return false;
}

void bfs(int src_y, int src_x, vector<vector<int>> &dist){    
    queue<pair<int, int>> q;
    dist[src_y][src_x] = 0;
    q.push(make_pair(src_y, src_x));
    while (!q.empty()){
        int y = q.front().first, x = q.front().second; q.pop();
        for (int i = 0 ; i < 4 ; ++i){
            int ny = y+DY[i], nx = x+DX[i];
            if (ny>=0 && ny < N && nx >=0 && nx < K && MAP[ny][nx] == '.' && dist[ny][nx]==-1){
                dist[ny][nx] = dist[y][x]+1;
                q.push(make_pair(ny,nx));
            }
        }
    }
}

void solv(){
   int P_CNT =0, E_CNT; // 사람수, 출구수
    for (int i = 0 ; i < N ; ++i)
        for (int j = 0 ; j < K ; ++j){
            switch (MAP[i][j]) {
                case 'D':
                    EXIT.push_back(make_pair(i,j));
                    break;
                case '.':
                    P_CNT++;
                    break;
            }
        }
    E_CNT = EXIT.size(); // 출구수

    // 특이 케이스
    if (P_CNT == 0){ cout << 0; return; }
    if (E_CNT == 0){ cout << "impossible"; return; }

    int A_LEN = E_CNT * P_CNT; // 출구수 * 최대시간(==사람수)
    int B_LEN = N*K; 
    // adj.resize(A_LEN);
    adj = vector<vector<pair<int,int>>>(A_LEN);
    // aMatch.resize(A_LEN, -1); // 출구가 3개일때 012 -> 1초 , 345 -> 2초 , 678 -> 3초
    bMatch.resize(B_LEN, -1);

    for (unsigned i = 0 ; i < EXIT.size() ; ++i){
        vector<vector<int>> dist(N , vector<int> (K, -1)); // 초기화
        bfs(EXIT[i].first, EXIT[i].second , dist);

        for (int y = 1 ; y < N-1 ; ++y)
            for (int x = 1 ; x < K-1 ; ++x)
                if (dist[y][x] > 0 && MAP[y][x] == '.'){
                    int src = (dist[y][x]-1)*E_CNT + i;
                    int dest = y*K+x;
                    for ( ;src < A_LEN; src += E_CNT)
                        adj[src].push_back(make_pair(dist[y][x], dest));
                }
    }
    // sort
    for (unsigned i = 0 ; i < adj.size() ; ++i) sort(adj[i].begin(), adj[i].end());

    int max_match = 0;
    int max_a_node = -1;
    for (unsigned i = 0 ; i < (unsigned)A_LEN ; ++i){
        vector<bool> visited(A_LEN, false); // 초기화
        if (dfs(i, visited, max_a_node)) 
            if (++max_match == P_CNT) break;
    }

    if (max_match != P_CNT) cout << "impossible";
    else{
        int min_time = (max_a_node/E_CNT)+1;
        cout << min_time;
    } 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0 ; i < N ; ++i)
        for (int j = 0 ; j < K ; ++j)
            cin >> MAP[i][j];
    solv();
}
