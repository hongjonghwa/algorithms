#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cassert>
#define INF 987654321
using namespace std;
int T;
int N, I, G, S, M, R;
int flow[1001][1001];

struct edge{
    int to;
    int capacity, flow;
    int reverse, next;
} EDGE[4010*110];
int adj_cnt;
int ADJ_ROOT[1001*101];
pair<int,int> parent [1002*101];

int network_flow(int source, int E){
    int total_flow = 0;
    for(;;){
        queue<int> q;
        memset(parent, -1, sizeof(parent));

        parent[source] = make_pair(source, -1);
        q.push(source);
        while (!q.empty()){
            int here =  q.front(); q.pop();
            /*
            cout << "here traverse << " << here  << " :";
            for (int p = ADJ_ROOT[here] ; p ; p = EDGE[p].next){
                int there = EDGE[p].to;
                cout << " " << there;
            }
            cout << "\n";
            */
            for (int p = ADJ_ROOT[here] ; p ; p = EDGE[p].next){
                int there = EDGE[p].to;
                int capacity = EDGE[p].capacity;
                int flow = EDGE[p].flow ;
                if (parent[there].first == -1 && capacity - flow > 0 ){
                    // cout << "here " << here << " there " << there << " capacity " << capacity << " flow " << flow << "\n" ;
                    q.push(there);
                    // cout << "push " << there<< "\n";
                    parent[there] = make_pair(here, p);
                }
            }
        }

        int sink = E * 101 + S;

        // cout << "check parent " << sink << " " << parent[sink].first << "\n";
        if (parent[sink].first == -1) break; // sink 까지 못 갔으면, 

        int amount = INF;
        for (int p = sink ; p != source ; p = parent[p].first){
            // cout << p << " <- ";
            int p_edge = parent[p].second;
            int remain =  EDGE[p_edge].capacity - EDGE[p_edge].flow;
            if (amount > remain) amount = remain;
        }
        // cout << source << " ] \n";
        // cout << "flow : " << amount << "\n";
        for (int p = sink ; p != source ; p = parent[p].first){
            // cout << p << " <- ";
            int &p_edge = parent[p].second; 
            EDGE[p_edge].flow += amount;
            EDGE[EDGE[p_edge].reverse].flow -= amount;
        }
        
        total_flow += amount;
        if (total_flow >= G) break;
    }
    
    return total_flow > G ? G : total_flow;
}

void add_edge(int a, int b, int capacity){
    // cout << " ADD EDGE : " << a << " , " << b << " , " << capacity << "\n";
    int u = ++adj_cnt;
    int v = ++adj_cnt;
    EDGE[u].to = b;
    EDGE[u].capacity = capacity;
    EDGE[u].flow = 0;
    EDGE[u].next = ADJ_ROOT[a];
    EDGE[u].reverse = v;
    ADJ_ROOT[a] = u;

    EDGE[v].to = a;
    EDGE[v].capacity = 0;
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
            for (int t = 0 ; t <= S ; ++t) // 
                add_edge(h*101+t, t, INF); // hospital, sink, time(cost), capacity
        }

        cin >> R;
        int a, b, capa, time;
        for (int r = 0 ; r < R ; ++r) {
            cin >> a >> b >> capa >> time;
            for (int t = 0 ; t+time <= S ; ++t)
                add_edge(a*101+t, b*101+t+time, capa);
        }

        // super sink
        for (int i = 0 ; i <= N ; ++i)
            for ( int t = 0 ; t < S ; ++t)
                add_edge(i*101+t, i*101+t+1, INF);
        

        /*
        for (int i = 1 ; i <= adj_cnt ; ++i){
            cout << i << ",";
            cout << EDGE[i].next << ",";
            cout << EDGE[i].reverse << ",";            
            cout <<"\n"; 
        }
        */
            
        // for (int i = 0 ; i <= N ; ++i) cout << "ADJ_ROOT[" << i << "] " << ADJ_ROOT[i] << "\n";

        cout << network_flow(I*101, 0) << "\n";
    }
}