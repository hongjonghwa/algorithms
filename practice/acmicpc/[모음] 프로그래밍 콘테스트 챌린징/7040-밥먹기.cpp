#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#define INF 987654321

using namespace std;

template<class T>
inline void SWAP(T & a, T & b){
    T tmp = a; a = b; b = tmp;
}

int dist[1001];
vector<pair<int, int>> adj[1001];

int N, ML, MD; // (2 ≤ N ≤ 1,000), (1 ≤ ML ≤ 10,000), (1 ≤ MD ≤ 10,000)



int solv(){
    dist[1] = 0;
    for (int i =  2 ; i <= N ; ++i) dist[i] = INF;

    bool updated = false;
    for (int v = 0 ; v < N ; ++v){
        updated = false;
        for (int here = 1 ; here <= N ; ++here){
            for (auto i  : adj[here]){
                int there = i.first, w = i.second;
                if (dist[here] + w < dist[there]){
                    dist[there] = dist[here] + w;
                    updated = true;
                }
            }
        }
    }
    if (updated) // 음수 싸이클
        return -1;

    // for (int i = 1 ; i <= N ; ++i) printf("%d %d \n", i, dist[i]);
    return dist[N] >= INF ? -2 : dist[N]; // 무한대는 -2
}

int main(){
    if (scanf("%d%d%d", &N, &ML, &MD) != 3) return EXIT_FAILURE;
    for (int i = 0 ; i < ML ; ++i){
        int a, b, d;
        if (scanf("%d%d%d", &a, &b, &d) != 3) return EXIT_FAILURE;
        adj[a].push_back(make_pair(b, d));
    }
    for (int i = 0 ; i < MD ; ++i){
        int a, b, d;
        if (scanf("%d%d%d", &a, &b, &d) != 3) return EXIT_FAILURE;
        adj[b].push_back(make_pair(a, -d)); // 최단거리
    }
    /*
    주의!
      소들은 꼭 번호 순서로 정렬해 있지 않아도 된다. (잘못 이해한 부분)
    */
    

    int ans = solv();
    printf("%d\n", ans);
}