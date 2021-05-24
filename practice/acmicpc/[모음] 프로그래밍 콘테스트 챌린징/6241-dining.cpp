#include<cstdio>
#include<vector>
#include<queue>

using namespace std;
struct edge{
    int to, capacity, flow;
    edge * reverse;
    edge(int t, int c, int f): to(t), capacity(c), flow(f){};
    edge(int t, int c): to(t), capacity(c), flow(0){};
};
vector<vector<edge*>> adj; // source 0, cows 1 to N, foods N+1 to N+F, drinks N+F+1 to N+F+D, sink N+F+D+1
void make_edge(int from, int to, int capacity){
    edge *u = new edge(to, capacity);
    edge *v = new edge(from, 0);
    u->reverse = v;
    v->reverse = u;
    adj[from].push_back(u);
    adj[to].push_back(v);
}

int N, F, D;

void bfs(int n, vector<int> & parent){
    queue<int> q;
    q.push(n);
    parent[n] = n;
    while (!q.empty()){
        int here = q.front(); q.pop();
        for (unsigned i = 0 ; i < adj[here].size() ; i++){
            edge *p = adj[here][i];
            if (parent[p->to] == -1 && p->capacity - p->flow > 0 ){
                parent[p->to] = here;
                q.push(p->to);
            }
        }
    }
}

int max_flow(int source, int sink){
    int ret = 0;
    for (;;){
        // bfs
        vector<int> parent(sink+1, -1);
        vector<edge*> path(sink+1);

        queue<int> q;
        q.push(source);
        parent[source] = source;
        while (!q.empty()){
            int here = q.front(); q.pop();
            for (unsigned i = 0 ; i < adj[here].size() ; i++){
                edge *p = adj[here][i];
                if (parent[p->to] == -1 && p->capacity - p->flow > 0 ){
                    parent[p->to] = here;
                    path[p->to] = p;
                    q.push(p->to);
                }
            }
        }

        if (parent[sink] == -1) break;

        // for (int p = sink ; p != parent[p] ; p = parent[p]) printf("%d<-", p);
        // printf("%d\n", source);

        for (int p = sink ; p != parent[p] ; p = parent[p]){
            path[p]->flow++;
            path[p]->reverse->flow--;
        }
        ret++;

    }
    return ret;
}

int main(){
    if (scanf("%d%d%d", &N, &F, &D) != 3) return 1;

    adj = vector<vector<edge*>>(N*2+F+D+2);
    int source = 0, sink = N*2+F+D+1, c_o = 0, f_o = N*2, d_o = N*2+F;
    for (int f = 1 ; f <= F ; ++f) make_edge(source,f_o+f,1);
    for (int c = 1 ; c <= N ; ++c) make_edge(c_o+c,c_o+N+c,1); // vectex의 유량을 제한하기 위해 둘로 나눔
    for (int d = 1 ; d <= D ; ++d) make_edge(d_o+d,sink,1);

    int f_cnt, d_cnt, t;
    for (int c = 1 ; c <= N ; ++c){
        if (scanf("%d%d", &f_cnt, &d_cnt) != 2) return 1;
        for (int i=0; i < f_cnt ; ++i){
            if (scanf("%d", &t) != 1) return 1;
            make_edge(f_o+t, c_o+c,1);
        }
        for (int i=0; i < d_cnt ; ++i){
            if (scanf("%d", &t) != 1) return 1;
            make_edge(c_o+N+c, d_o+t, 1);
        }
    }

    printf("%d", max_flow(source, sink));
}
