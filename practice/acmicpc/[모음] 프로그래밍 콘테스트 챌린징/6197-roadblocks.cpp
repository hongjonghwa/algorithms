#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
vector<pair<int, int >> adj[5001];

template<class T>
inline void SWAP(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}


int DISTANCE[2][5001];
int N, R; // 1 <= N <= 5000, 1 <= R <= 100,000

int solv(){

    for (int i = 1 ; i <= N ; ++i) DISTANCE[0][i] = DISTANCE[1][i] = 987654321;
    DISTANCE[0][1] = 0;

    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(-0, 1));

    int cnt = 0;
    while (!pq.empty()){
        int dist = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        // printf("here %d dist %d\n", here, dist);
        if (here == N) {
            cnt++;
            if (cnt == 2) return dist;
        }

        for (auto i : adj[here]){
            int there = i.first;
            int d = i.second;
            // printf("there %d d %d\n", there, d);
            if (dist + d ==  DISTANCE[0][there]) continue; // shortest path 가 여러개일 때 무시!
            if (dist + d < DISTANCE[1][there] ){
                DISTANCE[1][there] = dist + d;
                pq.push(make_pair( -(dist+d), there));
                if (DISTANCE[0][there] > DISTANCE[1][there] ) SWAP(DISTANCE[0][there], DISTANCE[1][there]);
            }
        }
    }
    return -1; // can't be

}

int main(){
    if (scanf("%d%d", &N, &R) != 2) return EXIT_FAILURE;
    for (int i = 0 ; i < R ; ++i){
        int a, b, d;
        if (scanf("%d%d%d", &a, &b, &d) != 3) return EXIT_FAILURE;
        adj[a].push_back(make_pair(b, d));
        adj[b].push_back(make_pair(a, d));
    }

    int ans = solv();
    printf("%d\n", ans);

}