/*

# 반례 
---------------
11 12
XXXXXXXXXXXX
X..........D
X.XXXXXXXXXX
X..........X
XXXXXXXXXX.X
X..........D
X.XXXXXXXXXX
X..........X
XXXXXXXXXX.X
X..........D
XXXXXXXXXXXX
---------------
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

vector<vector<int>> adj;
vector<int> aMatch,bMatch;

bool dfs(int n, vector<bool> &visited, int &max_b_node){
    if (visited[n]) return false;
    visited[n]= true;
    
    for (unsigned i = 0 ; i < adj[n].size() ; ++i){
        int there = adj[n][i];
        if (bMatch[there] == -1 || dfs(bMatch[there], visited, max_b_node)){
            if (there > max_b_node) max_b_node = there;
            aMatch[n] = there;
            bMatch[there] = n;
            //cout << " matched " << n << " - " << there << "\n";
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

void report_match_map(int E_CNT){
    cout << "!!! \n";
        //matching !!!
    for (int i = 0 ; i < N ; ++i){
        for (int j = 0 ; j < K ; ++j){
            if (MAP[i][j] == '.' && aMatch[i*K+j] != -1 ) cout << aMatch[i*K+j]%E_CNT;
            else cout << MAP[i][j];
        }
        cout << "\n";
    }
    cout << "\n";

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

    int A_LEN = N*K;
    int B_LEN = E_CNT * P_CNT; // 출구수 * 최대시간(==사람수)
    adj.resize(A_LEN);
    aMatch.resize(A_LEN, -1);
    bMatch.resize(B_LEN, -1); // 출구가 3개일때 012 -> 1초 , 345 -> 2초 , 678 -> 3초

    // make edge
    // adj[src][] 내부의 B간선 번호는 오름차순이여야 한다.
    // 1) 정렬된 상태로 쌓거나 2) 쌓은 후 정렬하거나...
    for (unsigned i = 0 ; i < EXIT.size() ; ++i){
        vector<vector<int>> dist(N , vector<int> (K, -1)); // 초기화
        bfs(EXIT[i].first, EXIT[i].second , dist);
        /*
        for (int i = 0 ; i < N ; ++i){
            for (int j = 0 ; j < K ; ++j) cout << " " << dist[i][j];
            cout << "\n";
        }
        cout << "\n";
        */
        for (int y = 0 ; y < N ; ++y)
            for (int x = 0 ; x < K ; ++x)
                if (dist[y][x] > 0 && MAP[y][x] == '.'){
                    int src = y*K+x;
                    int dest = (dist[y][x]-1)*E_CNT + i;
                    for ( ;dest < B_LEN; dest += E_CNT)
                        adj[src].push_back(dest);
                }
    }
    // sort
    for (unsigned i = 0 ; i < adj.size() ; ++i) sort(adj[i].begin(), adj[i].end());
    /*
    for (unsigned i = 0 ; i < adj.size() ; ++i){
        cout << " " << i << ":";
        for (unsigned j = 0 ; j < adj[i].size() ; ++j) cout << " " << adj[i][j];
        cout << "\n";
    }
    cout << "\n";
    */

    int max_match = 0;
    int max_b_node = -1;
    for (unsigned i = 0 ; i < (unsigned)A_LEN ; ++i){
        vector<bool> visited(A_LEN, false); // 초기화
        if (dfs(i, visited, max_b_node)) {
            max_match++;
            // report_match_map(E_CNT);
            if (max_match == P_CNT) break;
        }

    }

    // report_match_map(E_CNT);
    if (max_match != P_CNT) cout << "impossible";
    else{
        int min_time = (max_b_node/E_CNT)+1;
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
