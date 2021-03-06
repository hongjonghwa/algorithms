#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cassert>
#define INF 987654321
using namespace std;
int T;
int N, I, G, S, M, R;

struct edge{
    int to;
    int capacity, flow;
    int cost;
    int reverse, next;
} EDGE[3010];
int adj_cnt;
int ADJ_ROOT[1001];
pair<int,int> parent [1001]; // pair(node, edge)
int dist[1001];

int network_flow(int source, int sink){
    int total_flow = 0;
    for(;;){
        memset(parent, -1, sizeof(parent));
        memset(dist, 63, sizeof(dist));
        queue<int> q;

        parent[source] = make_pair(source, -1);
        dist[source] = 0;
        q.push(source);
        while (!q.empty()){
            int here =  q.front(); q.pop();

            for (int p = ADJ_ROOT[here] ; p ; p = EDGE[p].next){
                int there = EDGE[p].to;
                int capacity = EDGE[p].capacity;
                int flow = EDGE[p].flow;
                int there_dist = dist[here] + EDGE[p].cost;

                if (
                    capacity - flow > 0 
                    && dist[there] > there_dist 
                    && there_dist <= S
                    // && parent[there].first == -1 // ver1 과 달리 parent 로 돌아갈 수 있어야 한다
                    // --> 음수 사이클이 없으니 dijkstra 로 구현하여도 되지만, 유량이 적으니 dfs 도 무방할 듯.
                ){
                    q.push(there);
                    dist[there] = there_dist;
                    parent[there] = make_pair(here, p);
                }
            }
        }

        if (parent[sink].first == -1) break; // sink 까지 못 갔으면, 

        int amount = INF;
        for (int p = sink ; p != source ; p = parent[p].first){
            int p_edge = parent[p].second;
            int remain =  EDGE[p_edge].capacity - EDGE[p_edge].flow;
            if (amount > remain) amount = remain;
        }
        for (int p = sink ; p != source ; p = parent[p].first){
            int &p_edge = parent[p].second; 
            EDGE[p_edge].flow += amount;
            EDGE[EDGE[p_edge].reverse].flow -= amount;
        }
        
        total_flow += amount * (S-dist[sink] + 1);
        if (total_flow >= G) break;
    }
    
    return total_flow > G ? G : total_flow;
}

void add_edge(int a, int b, int capacity, int cost){
    int u = ++adj_cnt;
    int v = ++adj_cnt;
    EDGE[u].to = b;
    EDGE[u].capacity = capacity;
    EDGE[u].cost = cost;
    EDGE[u].flow = 0;
    EDGE[u].next = ADJ_ROOT[a];
    EDGE[u].reverse = v;
    ADJ_ROOT[a] = u;

    EDGE[v].to = a;
    EDGE[v].capacity = 0;
    EDGE[v].cost = -cost;
    EDGE[v].flow = 0;
    EDGE[v].next = ADJ_ROOT[b];
    EDGE[v].reverse = u;
    ADJ_ROOT[b] = v;
}

int main(){
    cin >> T;
    for (int testcase = 0 ; testcase < T ; ++testcase){
        // cout << "# TEST: " << testcase+1 << "\n";
        // init
        adj_cnt = 0;
        memset(ADJ_ROOT, 0, sizeof(ADJ_ROOT));

        cin >> N;
        cin >> I >> G >> S;
        cin >> M;
        
        int h; // hospital
        for (int m = 0 ; m < M ; ++m){
            cin >> h;
            add_edge(h, 0, INF, 0); // hospital, sink, capacity, cost
        }

        cin >> R;
        int a, b, capa, cost;
        for (int r = 0 ; r < R ; ++r) {
            cin >> a >> b >> capa >> cost;
            add_edge(a, b, capa, cost);
        }

        cout << network_flow(I, 0) << "\n";
    }
}